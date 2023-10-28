/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:43:49 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/28 19:48:06 by fkoolhov         ###   ########.fr       */
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

char	**add_quotes_to_strings(char **split_value)
{
	char	*temp;
	int		i;

	i = 0;
	while (split_value[i])
	{
		temp = split_value[i];
		split_value[i] = ft_strjoin("\"", split_value[i]);
		free(temp);
		if (split_value[i] == NULL)
			return (malloc_error_return_null("expander")); // free split value
		temp = split_value[i];
		split_value[i] = ft_strjoin(split_value[i], "\"");
		if (split_value[i] == NULL)
			return (malloc_error_return_null("expander")); // free split value
		free(temp);
		i++;
	}
	return (split_value);
}

int	get_new_value(t_expander_var *var, t_htable *env)
{
	char	*key;

	var->key_start = var->index;
	var->index++;
	if (end_of_expandable_is_found(var->token->value[var->index]))
		return (EXIT_SUCCESS);
	while (!end_of_expandable_is_found(var->token->value[var->index]))
		(var->index)++;
	var->key_len = var->index - var->key_start;
	if (!ft_isspace(!var->token->value[var->index]))
		var->concatenate_end = true;
	key = ft_substr(var->token->value, var->key_start, var->index - var->key_start);
	if (key == NULL)
		return (malloc_error_return_failure("expander"));
	var->new_value = find_env_value(env, key);
	free(key);
	return (EXIT_SUCCESS);
}

int	split_value_and_update_list(t_expander_var *var)
{
	var->split_value = split_token_value(var->new_value, var->token->type);
	if (var->split_value == NULL)
		return (EXIT_FAILURE);
	if (!ft_isspace(var->new_value[0]) || (var->key_start == 0))
		var->concatenate_begin = true;
	else
		var->concatenate_begin = false;
	if (ft_isspace(var->new_value[ft_strlen(var->new_value) - 1]))
		var->concatenate_end = false;
	else
		var->concatenate_end = true;
	var->split_value = add_quotes_to_strings(var->split_value);
	if (var->split_value == NULL)
		return (EXIT_FAILURE);
	else
	{
		if (update_list(var) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	expand_variable(t_expander_var *var, t_htable *env)
{
	if (get_new_value(var, env) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (var->new_value == NULL)
	{
		replace_var(var, var->new_value);
		if (var->key_start > 0)
			var->index = var->key_start - 1;
		else
			var->index = 0;
		return (EXIT_SUCCESS);
	}
	else
	{
		if (split_value_and_update_list(var) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
