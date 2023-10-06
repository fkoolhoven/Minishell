/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:51:01 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 16:52:58 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*lstlast_command(t_command *lst)
{
	t_command	*ptr_cur;
	t_command	*ptr_prv;

	if (lst == NULL)
		return (lst);
	ptr_cur = lst;
	ptr_prv = NULL;
	while (ptr_cur != NULL)
	{
		ptr_prv = ptr_cur;
		ptr_cur = ptr_cur->next;
	}
	return (ptr_prv);
}

t_command	*lstnew_command(char **command, t_redirect *in, t_redirect *out)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (node == NULL)
		return (NULL);
	node->command = command;
	node->in = in;
	node->out = out;
	node->next = NULL;
	return (node);
}

void	lstadd_back_command(t_command **lst, t_command *new)
{
	t_command	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = lstlast_command(*lst);
		last->next = new;
	}
}
