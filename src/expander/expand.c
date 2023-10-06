/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 16:54:07 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Skips over everything in between single quotes, while still
// respecting single quotes that are in between double quotes
bool	prevent_expansion_in_single_quotes(t_token *token, int *i)
{
	static bool	in_double_quotes;

	if (token->value[*i] == '\"')
	{
		if (in_double_quotes == false)
			in_double_quotes = true;
		else
			in_double_quotes = false;
		return (true);
	}
	else if (!in_double_quotes && token->value[*i] == '\'')
	{
		*i = find_next_quote(token->value, *i);
		return (true);
	}
	return (false);
}

// Sends only expandables that are not in between single quotes
// to the expand_variable function
int	find_expandables(t_token *token, t_htable *env)
{
	bool	quote_check;
	int		i;

	quote_check = false;
	i = 0;
	while (token->value[i])
	{
		quote_check = prevent_expansion_in_single_quotes(token, &i);
		if (!token->value[i])
			return (EXIT_SUCCESS);
		if (!quote_check && token->value[i] == '$')
		{
			if (expand_variable(token, env, &i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// Goes through the list of tokens
int	expand(t_list **list_start, t_htable *env)
{
	t_token	*current_token;
	t_list	*tokens;

	tokens = *list_start;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		if (find_expandables(current_token, env) == EXIT_FAILURE)
		{
			terminate_token_list_error(list_start);
			return (EXIT_FAILURE);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
