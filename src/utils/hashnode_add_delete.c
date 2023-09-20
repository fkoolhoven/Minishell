/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   hashnode_add_delete.c                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/20 16:15:12 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/20 16:44:47 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	hasharray_delone(t_hnode *node)
{
	if (node != NULL)
	{
		if (node->key != NULL)
			free(node->key);
		if (node->value != NULL)
			free(node->value);
		free(node);
	}
}

void	hasharray_clear(t_hnode **array)
{
	t_hnode	*tmp_cur;
	t_hnode	*tmp_prv;

	if (array != NULL)
	{
		tmp_cur = *array;
		while (tmp_cur != NULL)
		{
			tmp_prv = tmp_cur;
			tmp_cur = tmp_cur->next;
			hasharray_delone(tmp_prv);
		}
		*array = NULL;
	}
}

void	hasharray_add_back(t_hnode **array, t_hnode *new)
{
	t_hnode	*last;

	if (array != NULL)
	{
		if (*array == NULL)
			(*array) = new;
		else
		{
			last = hasharray_last(*array);
			last->next = new;
		}
	}
}

void	hasharray_add_front(t_hnode **array, t_hnode *new)
{
	if (array != NULL)
	{
		if (*array == NULL)
			(*array) = new;
		else
		{
			new->next = *array;
			(*array) = new;
		}
	}
}
