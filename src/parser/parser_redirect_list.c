/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:50:44 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 17:00:52 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
