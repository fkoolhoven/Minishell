/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 20:23:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*initialize_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (malloc_error_return_null("tokenizer"));
	token->type = -1;
	token->value = NULL;
	return (token);
}

static int	add_token_to_list(t_list **tokens, t_token *token)
{
	t_list	*new_node;

	if (*tokens)
	{
		new_node = ft_lstnew(token);
		if (new_node == NULL)
			return (malloc_error_return_failure("tokenizer"));
		ft_lstadd_back(tokens, new_node);
	}
	else
	{
		*tokens = ft_lstnew(token);
		if (*tokens == NULL)
			return (malloc_error_return_failure("tokenizer"));
	}
	return (EXIT_SUCCESS);
}

static int	tokenize_input(t_token *token, char *input, int *i, int *exit_code)
{
	if (char_is_operator(input[*i]))
	{
		if (tokenize_operator(token, input, i, exit_code) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (tokenize_word(token, input, i) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	find_beginning_of_command(char *input, int *i, int *exit_code)
{
	bool	perform_syntax_check;

	if (*i == 0)
		perform_syntax_check = true;
	while (ft_isspace(input[*i]) && input[*i])
		(*i)++;
	if (perform_syntax_check && input[*i] == '|')
		return (syntax_error_return_failure("starting with pipe", exit_code));
	if (!input[*i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Goes through the use input string and splits it up into tokens
// that have type word or a redirection type. Creates a linked list
// (tokens), node's value pointing to a token of type t_token.
t_list	*tokenizer(char *input, int *exit_code)
{
	t_list	*tokens;
	t_token	*token;
	int		check;
	int		i;

	*exit_code = EXIT_FAILURE;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		check = find_beginning_of_command(input, &i, exit_code);
		if (check != EXIT_SUCCESS)
			break ;
		token = initialize_token();
		if (!token)
			return (terminate_token_list_error_null(&tokens));
		if (add_token_to_list(&tokens, token) == EXIT_FAILURE)
		{
			free(token);
			return (terminate_token_list_error_null(&tokens));
		}
		if (tokenize_input(token, input, &i, exit_code) == EXIT_FAILURE)
			return (terminate_token_list_error_null(&tokens));
	}
	return (tokens);
}
