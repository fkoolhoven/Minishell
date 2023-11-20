/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remove_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:40:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/20 11:55:50 by fkoolhov         ###   ########.fr       */
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

int	rm_empty_tokens(t_list **list_start)
{
	t_list	*current;
	t_list	*previous;
	t_token	*token;
	int		token_type;

	current = *list_start;
	previous = NULL;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (token->value == NULL)
		{
			token_type = token->type;
			remove_current_token(&current, list_start, previous);
			if (token_type != WORD)
				return (minishell_error_return_failure("ambiguous redirect"));
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}
