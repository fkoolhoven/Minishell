/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:43:49 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 21:43:19 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	end_of_expandable_is_found(char c)
{
	if (c == '\0')
		return (true);
	else if (ft_isspace(c))
		return (true);
	else if (c == '?')
		return (true);
	else if (c == '$')
		return (true);
	else if (char_is_quote(c))
		return (true);
	return (false);
}

static int	get_new_value(t_expander_var *var, t_htable *env)
{
	char	*key;
	int		key_len;

	var->key_start = var->i;
	var->i++;
	if (end_of_expandable_is_found(var->token->value[var->i]))
		return (EXIT_SUCCESS);
	while (!end_of_expandable_is_found(var->token->value[var->i]))
		(var->i)++;
	var->key_len = var->i - var->key_start;
	if (!ft_isspace(!var->token->value[var->i]))
		var->cat_end = true;
	key_len = var->i - var->key_start;
	key = ft_substr(var->token->value, var->key_start, key_len);
	if (key == NULL)
		return (malloc_error_return_failure("expander"));
	var->new_value = find_env_value(env, key);
	free(key);
	return (EXIT_SUCCESS);
}

int	expand_variable(t_expander_var *var, t_htable *env)
{
	int	new_index;

	if (get_new_value(var, env) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (var->token->value[var->i] == '?')
		return (EXIT_SUCCESS);
	else if (var->new_value == NULL)
		return (replace_var(var, var->new_value, var->key_start));
	else if (var->in_double_quotes)
	{
		new_index = var->key_start + ft_strlen(var->new_value - 1);
		return (replace_var(var, var->new_value, new_index));
	}
	if (split_token_value(var) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	set_concatenate_bools(var);
	if (update_list(var) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
