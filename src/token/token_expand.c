/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/18 13:52:05 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	prevent_expansion_in_single_quotes(t_token *token, int *i)
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

static int	find_expandables(t_token *token, t_htable *env)
{
	bool	quote_check;
	int		exit_code;
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
			exit_code = expand_variable(token, env, &i);
			if (exit_code != EXIT_SUCCESS)
				return (exit_code);
		}
		if (token->value[i])
			i++;
	}
	return (EXIT_SUCCESS);
}

static void	remove_token_from_list(t_list **list_start, int index_to_remove)
{
	int		i;
	t_list	*to_delete;
	t_list	*token;

	token = *list_start;
	i = 0;
	if (index_to_remove == 0)
		*list_start = (*list_start)->next;
	else
	{
		while (i != index_to_remove - 1)
		{
			token = token->next;
			i++;
		}
		to_delete = token->next;
		token->next = to_delete->next;
		token = to_delete;
	}
	terminate_token(token);
}

int	expand_tokens(t_list **list_start, t_htable *env)
{
	t_token	*current_token;
	t_list	*tokens;
	int		exit_code;
	int		token_index;

	tokens = *list_start;
	token_index = 0;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		exit_code = find_expandables(current_token, env);
		if (exit_code == EXIT_FAILURE)
		{
			terminate_token_list_error(list_start);
			return (EXIT_FAILURE);
		}
		tokens = tokens->next;
		if (exit_code == VALUE_NOT_FOUND && current_token->value == NULL)
			remove_token_from_list(list_start, token_index);
		else
			token_index++;
	}
	return (EXIT_SUCCESS);
}
