/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   process_functions.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 14:17:51 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/25 15:04:20 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*process_last(t_process *lst)
{
	t_process	*cur;
	t_process	*prev;

	if (lst == NULL)
		return (NULL);
	cur = lst;
	prev = NULL;
	while (cur != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	return (prev);
}

t_process	*process_make_add_node(t_process **lst, pid_t pid)
{
	t_process	*node;

	if (lst == NULL)
		return (NULL);
	node = processnode_new(pid);
	if (node == NULL)
		return (process_clear(lst), NULL);
	process_add_back(lst, node);
	return (*lst);
}
