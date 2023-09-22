/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 11:58:42 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_token	*initialize_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		printf("malloc error token\n");
		exit (EXIT_FAILURE);
	}
	token->type = -1;
	token->value = NULL;
	token->expand = false;
	return (token);
}

void	add_token_to_list(t_list **tokens, t_token *token)
{
	t_list	*new_node;

	if (*tokens)
	{
		new_node = ft_lstnew(token);
		if (*tokens == NULL)
		{
			printf("malloc error new tokens list node\n");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(tokens, new_node);
	}
	else
	{
		*tokens = ft_lstnew(token);
		if (*tokens == NULL)
		{
			printf("malloc error new tokens list\n");
			exit(EXIT_FAILURE);
		}
	}
}

t_list	*tokenize_input(char *input)
{
	t_list	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		token = initialize_token();
		add_token_to_list(&tokens, token);
		if (char_is_single_quote(input[i]))
			tokenize_single_quote(token, input, &i);
		else if (char_is_double_quote(input[i]))
			tokenize_double_quote(token, input, &i);
		else if (char_is_operator(input[i]))
			tokenize_operator(token, input, &i);
		else
			tokenize_word(token, input, &i);
	}
	if (!tokens)
		return (NULL);
	
	// expand_parameters(&tokens);
	return (tokens);
}