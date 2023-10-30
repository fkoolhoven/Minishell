/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 20:24:03 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_split_value_and_return(t_expander_var *var, int exit_code)
{
	var->i = 0;
	if (exit_code == EXIT_SUCCESS)
		free(var->split_value);
	else
		ft_free_str_array(var->split_value);
	return (exit_code);
}

static int	insert_token_with_split_value(t_expander_var *var, int j)
{
	t_list	*new_node;
	t_token	*new_token;

	new_node = create_new_node(var->split_value[j]);
	if (new_node == NULL)
		return (EXIT_FAILURE);
	new_token = new_node->content;
	insert_token_into_list(new_node, var);
	return (EXIT_SUCCESS);
}

static int	insert_split_values_into_token_list(t_expander_var *var, int j)
{
	while (var->split_value[j])
	{
		var->i = ft_strlen(var->split_value[j]) - 1;
		var->token = (t_token *)var->tokens->content;
		if (var->cat_end && !var->split_value[j + 1])
		{
			if (concatenate_end(var, j) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			break ;
		}
		if (insert_token_with_split_value(var, j) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		var->tokens = var->tokens->next;
		j++;
	}
	return (EXIT_SUCCESS);
}

int	update_list(t_expander_var *var)
{
	int		j;
	int		error_check;

	j = 0;
	error_check = check_for_simple_replace(var, j);
	if (error_check != CONTINUE)
		return (free_split_value_and_return(var, error_check));
	if (split_token_end_after_key(var) == EXIT_FAILURE)
		return (free_split_value_and_return(var, EXIT_FAILURE));
	if (split_token_beginning_before_key(var) == EXIT_FAILURE)
		return (free_split_value_and_return(var, EXIT_FAILURE));
	j = replace_token_value(var, j);
	if (!var->split_value[j])
		return (free_split_value_and_return(var, EXIT_SUCCESS));
	error_check = concatenate_begin(var, &j);
	if (error_check != CONTINUE)
		return (free_split_value_and_return(var, error_check));
	if (insert_split_values_into_token_list(var, j) == EXIT_FAILURE)
		return (free_split_value_and_return(var, EXIT_FAILURE));
	return (free_split_value_and_return(var, EXIT_SUCCESS));
}
