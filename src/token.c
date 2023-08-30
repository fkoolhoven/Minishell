/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/30 18:15:36 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include <ctype.h>

void	tokenize_word(t_token *token)
{
	token->type = COMMAND;
	return ;
}

void	tokenize_operator(t_token *token)
{
	token->type = OUTFILE;
	return ;
}

t_token	*initialize_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		exit (EXIT_FAILURE);
	}
	token->type = INFILE;
	token->value = "something";
	return (token);
}

bool	char_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

// "cat infile > outfile"
void	tokenize_input(char *input)
{
	t_list	*tokens;
	t_list	*new_node;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		while (isspace(input[i]))
			i++;
		token = initialize_token();
		if (tokens == NULL)
			tokens = ft_lstnew(token);
		else
		{
			new_node = ft_lstnew(token);
			ft_lstadd_back(&tokens, new_node);
		}
		if (char_is_operator(input[i]))
		{
			tokenize_operator(token);
		}
		else
		{
			tokenize_word(token);
		}
		i++;
	}
}
