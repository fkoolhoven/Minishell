/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/11 14:42:22 by fkoolhov         ###   ########.fr       */
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

int	add_token_to_list(t_list **tokens, t_token *token)
{
	t_list	*new_node;

	if (*tokens)
	{
		new_node = ft_lstnew(token);
		if (*tokens == NULL)
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

// Function too long
t_list	*tokenize_input(char *input)
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
		if (char_is_operator(input[i]))
		{
			if (tokenize_operator(token, input, &i) != EXIT_SUCCESS)
				return (terminate_token_list_error(&tokens));
		}
		else
			tokenize_word(token, input, &i);
	}
	if (!tokens)
		return (NULL);
	return (tokens);
}
