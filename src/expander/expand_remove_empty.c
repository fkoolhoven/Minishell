/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remove_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:40:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 21:42:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_current_token(t_list **current, t_list **list_start,
	t_list *previous)
{
	t_list	*to_delete;

	to_delete = *current;
	if (previous == NULL)
		*list_start = (*current)->next;
	else
		previous->next = (*current)->next;
	*current = (*current)->next;
	terminate_token(to_delete);
}

void	remove_empty_tokens_from_list(t_list **list_start)
{
	t_list	*current;
	t_list	*previous;
	t_token	*token;

	current = *list_start;
	previous = NULL;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (token->value == NULL)
			remove_current_token(&current, list_start, previous);
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
