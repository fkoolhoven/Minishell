/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:50:36 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 19:53:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_token_value(t_expander_var *var, int j)
{
	if ((size_t)var->key_len == ft_strlen(var->token->value))
	{
		free(var->token->value);
		var->token->value = var->split_value[j];
		var->i = ft_strlen(var->split_value[j]) - 1;
		var->cat_begin = false;
		j++;
	}
	return (j);
}

static bool	no_need_to_create_extra_tokens(t_expander_var *var, int j)
{
	if (!var->split_value[j + 1])
	{
		if (var->cat_begin && var->cat_end && !var->split_value[j + 1])
			return (true);
		else if ((size_t)var->key_len == ft_strlen(var->token->value))
			return (true);
	}
	return (false);
}

int	check_for_simple_replace(t_expander_var *var, int j)
{
	int	new_index;

	if (no_need_to_create_extra_tokens(var, j))
	{
		new_index = var->key_start + ft_strlen(var->split_value[j] - 1);
		if (replace_var(var, var->split_value[j], new_index))
			return (EXIT_FAILURE);
		free(var->split_value[j]);
		return (EXIT_SUCCESS);
	}
	return (CONTINUE);
}

int	replace_var(t_expander_var *var, char *new_value, int new_index)
{
	char	*new_str;
	int		end_len;
	int		new_str_len;

	end_len = ft_strlen(var->token->value) - var->key_start - var->key_len;
	new_str_len = var->key_start + ft_strlen(new_value) + end_len;
	if (new_str_len == 0)
	{
		free(var->token->value);
		var->token->value = NULL;
		return (EXIT_SUCCESS);
	}
	new_str = ft_calloc(new_str_len + 1, sizeof(char));
	if (new_str == NULL)
		return (malloc_error_return_failure("expander"));
	ft_strlcpy(new_str, var->token->value, var->key_start + 1);
	ft_strlcat(new_str, new_value, new_str_len + 1);
	ft_strlcat(new_str, var->token->value + var->key_start
		+ var->key_len, new_str_len + 1);
	free(var->token->value);
	var->token->value = new_str;
	var->i = new_index;
	return (EXIT_SUCCESS);
}
