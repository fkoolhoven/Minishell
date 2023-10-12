/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/12 17:21:58 by fkoolhov         ###   ########.fr       */
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
		i++;
	}
	return (EXIT_SUCCESS);
}

void	remove_token_from_list(t_list **list_start, int index_to_remove)
{
	int		i;
	t_list	*new_previous;
	t_list	*new_next;
	t_list	*to_delete;
	t_list	*token;

	token = *list_start;
	i = 0;
	if (index_to_remove == 0)
	{
		*list_start = (*list_start)->next;
		terminate_token(token);
	}
	else if (index_to_remove == ft_lstsize(*list_start))
		terminate_token(token);
	else
	{
		while (i != index_to_remove - 1)
		{
			token = token->next;
			i++;
		}
		new_previous = token;
		to_delete = token->next;
		new_next = to_delete->next;
		new_previous->next = new_next;
		terminate_token(to_delete);
	}
}

int	expand_tokens(t_list **list_start, t_htable *env)
{
	t_token	*current_token;
	t_list	*next_token;
	t_list	*tokens;
	int		exit_code;
	int		index;

	tokens = *list_start;
	index = 0;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		exit_code = find_expandables(current_token, env);
		if (exit_code == EXIT_FAILURE)
		{
			terminate_token_list_error(list_start);
			return (EXIT_FAILURE);
		}
		else if (exit_code == VALUE_NOT_FOUND)
		{
			next_token = tokens->next;
			remove_token_from_list(list_start, index);
			tokens = next_token;
		}
		else
		{
			tokens = tokens->next;
			index++;
		}
	}
	return (EXIT_SUCCESS);
}
