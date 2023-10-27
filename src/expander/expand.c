/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 16:26:48 by fkoolhov         ###   ########.fr       */
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

static int	find_expandables(t_list	**tokens, t_token *token, t_htable *env)
{
	bool	concatenate_begin;
	bool	quote_check;
	int		exit_code;
	int		i;

	quote_check = false;
	i = 0;
	while (token->value[i])
	{
		token = (t_token *)(*tokens)->content;
		printf("BEGINNING OF FIND EXPANDABLES LOOPS\n");
		quote_check = prevent_expansion_in_single_quotes(token, &i);
		if (!token->value[i])
			return (EXIT_SUCCESS);
		if (!quote_check && token->value[i] == '$')
		{
			if (i == 0 || !ft_isspace(token->value[i - 1]))
				concatenate_begin = true;
			exit_code = expand_variable(tokens, token, env, &i, concatenate_begin); // passing same token with same value
			if (exit_code != EXIT_SUCCESS)
				return (exit_code);
			token->was_expanded = true;
			concatenate_begin = false;
			printf("REPLACED EXPANDABLE IN FIND EXPANDABLES\n");
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
	int		error_check;
	int		token_index;

	tokens = *list_start;
	token_index = 0;
	while (tokens)
	{
		error_check = EXIT_SUCCESS;
		current_token = (t_token *)tokens->content;
		printf("IN EXPAND TOKENS BASE FUNC AT TOKEN %s\n\n", current_token->value);
		if (current_token->type != HEREDOC)
			error_check = find_expandables(&tokens, current_token, env);
		if (error_check == EXIT_FAILURE)
			return (terminate_token_list_error_failure(list_start));
		tokens = tokens->next;
		if (error_check == VALUE_NOT_FOUND && current_token->value == NULL)
			remove_token_from_list(list_start, token_index);
		else
			token_index++;
	}
	return (EXIT_SUCCESS);
}
