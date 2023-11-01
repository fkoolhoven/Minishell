/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   process_add_delete.c                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 14:04:29 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 13:57:11 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*processnode_new(pid_t pid)
{
	t_process	*node;

	node = malloc(sizeof(t_process));
	if (node == NULL)
		return (NULL);
	node->process = pid;
	node->next = NULL;
	return (node);
}

void	process_add_back(t_process **lst, t_process *new)
{
	t_process	*last;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = process_last(*lst);
			if (last != NULL)
				last->next = new;
		}
	}
}

void	process_add_front(t_process **lst, t_process *new)
{
	if (new != NULL && lst != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	process_delone(t_process *node)
{
	free(node);
}

void	process_clear(t_process **lst)
{
	t_process	*cur;
	t_process	*prev;

	if (lst != NULL)
	{
		cur = *lst;
		prev = NULL;
		while (cur != NULL)
		{
			prev = cur;
			cur = cur->next;
			process_delone(prev);
		}
		*lst = NULL;
	}
}
