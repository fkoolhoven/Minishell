/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_concatenate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:50:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/20 11:59:58 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	concatenate_end(t_expander_var *var, int j)
{
	char	*new_value;

	var->tokens = var->tokens->next;
	var->token = (t_token *)var->tokens->content;
	new_value = ft_strjoin(var->split_value[j], var->token->value);
	if (new_value == NULL)
		return (malloc_error_return_failure("expander"));
	free(var->token->value);
	var->token->value = new_value;
	return (EXIT_SUCCESS);
}

int	concatenate_begin(t_expander_var *var, int *j)
{
	char	*new_value;

	if (var->cat_begin)
	{
		new_value = ft_strjoin(var->token->value, var->split_value[*j]);
		if (new_value == NULL)
			return (malloc_error_return_failure("expander"));
		free(var->token->value);
		var->token->value = new_value;
		(*j)++;
		var->i = var->key_start + ft_strlen(var->split_value[*j]) - 1;
		if (var->tokens)
			var->token = (t_token *)var->tokens->content;
		else
			return (EXIT_SUCCESS);
	}
	return (CONTINUE);
}

void	set_concatenate_bools(t_expander_var *var)
{
	if (!ft_isspace(var->new_value[0]) || var->key_start == 0)
		var->cat_begin = true;
	else
		var->cat_begin = false;
	if (!ft_isspace(var->new_value[ft_strlen(var->new_value) - 1]))
		var->cat_end = true;
	else
		var->cat_end = false;
}
