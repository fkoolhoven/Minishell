/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_update_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:53:31 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 19:41:18 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_split_value(char **split_value, int j)
{
	while (split_value[j])
	{
		free(split_value[j]);
		j++;
	}
	return (malloc_error_return_null("expander"));
}

void	insert_token_into_list(t_list *new_node, t_expander_var *var)
{
	t_list	*temp;

	temp = var->tokens->next;
	var->tokens->next = new_node;
	new_node->next = temp;
}

void	*create_new_node(char *value)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = initialize_token();
	if (new_token == NULL)
		return (malloc_error_return_null("expander"));
	new_token->type = WORD;
	new_token->value = value;
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free (new_token);
		return (malloc_error_return_null("expander"));
	}
	return (new_node);
}
