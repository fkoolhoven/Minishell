/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/28 19:47:20 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	prevent_expansion_in_single_quotes(t_expander_var *var)
{
	static bool	in_double_quotes;

	if (var->token->value[var->index] == '\"')
	{
		if (in_double_quotes == false)
			in_double_quotes = true;
		else
			in_double_quotes = false;
		return (true);
	}
	else if (!in_double_quotes && var->token->value[var->index] == '\'')
	{
		var->index = find_next_quote(var->token->value, var->index);
		return (true);
	}
	return (false);
}

int	find_expandables(t_expander_var *var, t_htable *env)
{
	bool	quote_check;
	int		exit_code;

	quote_check = false;
	var->index = 0;
	while (var->token->value[var->index])
	{
		var->token = (t_token *)var->tokens->content;
		quote_check = prevent_expansion_in_single_quotes(var);
		if (!var->token->value[var->index])
			return (EXIT_SUCCESS);
		if (!quote_check && var->token->value[var->index] == '$')
		{
			if (var->index == 0 || !ft_isspace(var->token->value[var->index - 1]))
				var->concatenate_begin = true;
			exit_code = expand_variable(var, env);
			if (exit_code == EXIT_FAILURE)
				return (exit_code);
			var->concatenate_begin = false;
			if (var->tokens)
				var->token = (t_token *)var->tokens->content;
		}
		else
			var->index++;
		if (var->tokens == NULL)
			break ;
		if (var->token->value == NULL)
			break ;
	}
	return (EXIT_SUCCESS);
}

void	remove_empty_tokens_from_list(t_list **list_start)
{
	t_list	*to_delete;
	t_list	*tokens;
	t_token	*token;

	tokens = *list_start;
	token = (t_token *)tokens->content;
	while (tokens && token->value == NULL)
	{
		*list_start = (*list_start)->next;
		terminate_token(tokens);
		tokens = *list_start;
		if (tokens)
			token = (t_token *)tokens->content;
	}
	if (tokens)
	{
		while (tokens->next)
		{
			token = (t_token *)tokens->next->content;
			if (token->value == NULL)
			{
				to_delete = tokens->next;
				tokens->next = to_delete->next;
				terminate_token(to_delete);
			}
			tokens = tokens->next;
		}
	}
}

t_expander_var	*init_expander_vars(void)
{
	t_expander_var	*var;

	var = malloc(sizeof(t_expander_var));
	if (var == NULL)
		return (malloc_error_return_null("expander"));
	var->token = NULL;
	var->split_value = NULL;
	var->tokens = NULL;
	var->concatenate_begin = false;
	var->concatenate_end = false;
	var->key_start = 0;
	var->key_len = 0;
	var->index = 0;
	return (var);
}

int	expand_tokens(t_list **list_start, t_htable *env)
{
	t_expander_var	*var;

	var = init_expander_vars();
	var->tokens = *list_start;
	while (var->tokens)
	{
		var->token = (t_token *)var->tokens->content;
		if (var->token->type != HEREDOC)
		{
			if (find_expandables(var, env) != EXIT_SUCCESS)
				return (terminate_token_list_error_failure(list_start));
		}
		if (var->tokens)
			var->tokens = var->tokens->next;
	}
	remove_empty_tokens_from_list(list_start);
	free(var);
	return (EXIT_SUCCESS);
}
