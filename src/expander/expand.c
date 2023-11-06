/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/06 16:35:40 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	prevent_expansion_in_single_quotes(t_expander_var *var)
{
	if (var->token->value[var->i] == '\"')
	{
		if (var->in_double_quotes == false)
			var->in_double_quotes = true;
		else
			var->in_double_quotes = false;
		return (true);
	}
	else if (!var->in_double_quotes && var->token->value[var->i] == '\'')
	{
		var->i = find_next_quote(var->token->value, var->i);
		return (true);
	}
	return (false);
}

static int	find_expandables(t_expander_var *var, t_htable *env)
{
	bool	quote_check;

	quote_check = false;
	var->i = 0;
	while (var->tokens && var->token->value && var->token->value[var->i])
	{
		quote_check = prevent_expansion_in_single_quotes(var);
		if (!var->token->value[var->i])
			return (EXIT_SUCCESS);
		if (!quote_check && var->token->value[var->i] == '$')
		{
			if (expand_variable(var, env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (var->expanded_exit_status)
				free(var->expanded_exit_status);
		}
		else
			var->i++;
		if (var->tokens)
			var->token = (t_token *)var->tokens->content;
	}
	return (EXIT_SUCCESS);
}

static t_expander_var	*init_expander_vars(int exit_status)
{
	t_expander_var	*var;

	var = malloc(sizeof(t_expander_var));
	if (var == NULL)
		return (malloc_error_return_null("expander"));
	var->token = NULL;
	var->in_double_quotes = false;
	var->expanded_exit_status = NULL;
	var->split_value = NULL;
	var->tokens = NULL;
	var->cat_begin = false;
	var->cat_end = false;
	var->exit_status = exit_status;
	var->key_start = 0;
	var->key_len = 0;
	var->i = 0;
	var->token_was_split = false;
	var->no_key = false;
	return (var);
}

// Goes through linked list of tokens and expands environment variables,
// except when they are in between single quotes. Follows the same rules
// in regards to concatenation and splitting of expanded variables as bash.
int	expand_variables(t_list **list_start, t_htable *env, int exit_status)
{
	t_expander_var	*var;

	var = init_expander_vars(exit_status);
	if (var == NULL)
		return (terminate_token_list_error_failure(list_start));
	var->tokens = *list_start;
	while (var->tokens)
	{
		var->token = (t_token *)var->tokens->content;
		if (var->token->type != HEREDOC)
		{
			if (find_expandables(var, env) != EXIT_SUCCESS)
			{
				if (var->expanded_exit_status)
					free(var->expanded_exit_status);
				free(var);
				return (terminate_token_list_error_failure(list_start));
			}
		}
		if (var->tokens)
			var->tokens = var->tokens->next;
	}
	remove_empty_tokens_from_list(list_start);
	free(var);
	return (EXIT_SUCCESS);
}
