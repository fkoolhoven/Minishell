/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:00:42 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/05 17:54:44 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Contains the modified linked list functions from libft. Modified for command struct and redirect struct

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

t_redirect	*lstlast_redirect(t_redirect *lst)
{
	t_redirect	*ptr_cur;
	t_redirect	*ptr_prv;

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


t_redirect	*lstnew_redirect(int type, char *value)
{
	t_redirect	*node;

	node = malloc(sizeof(t_redirect));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	lstadd_back_redirect(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = lstlast_redirect(*lst);
		last->next = new;
	}
}

