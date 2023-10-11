/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/11 18:00:34 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*initialize_token(void)
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

static int	tokenize_input(t_token *token, char *input, int *i)
{
	if (char_is_operator(input[*i]))
	{
		if (tokenize_operator(token, input, i) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (tokenize_word(token, input, i) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Goes through the use input string and splits it up into tokens
// that have type word or a redirection type. Creates a linked list
// (tokens), node's value pointing to a token of type t_token.
t_list	*tokenizer(char *input)
{
	t_list	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		if (!input[i])
			break ;
		token = initialize_token();
		if (!token)
			return (terminate_token_list_error(&tokens));
		if (add_token_to_list(&tokens, token) == EXIT_FAILURE)
		{
			free(token);
			return (terminate_token_list_error(&tokens));
		}
		if (tokenize_input(token, input, &i) == EXIT_FAILURE)
			return (terminate_token_list_error(&tokens));
	}
	return (tokens);
}
