/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashnode_functions.c                              :+:    :+:             */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 14:03:59 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/20 15:28:51 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_hash_node	*new_hash_node(char *key, char *value)
{
	t_hash_node	*node;

	node = malloc(sizeof(t_hash_node));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_hash_node	*hasharray_last(t_hash_node *array)
{
	t_hash_node	*tmp;

	if (array == NULL)
		return (array);
	tmp = array;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	hasharray_add_back(t_hash_node **array, t_hash_node *new)
{
	t_hash_node	*last;

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

void	hasharray_add_front(t_hash_node **array, t_hash_node *new)
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

void	hasharray_delone(t_hash_node *node)
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

void	hasharray_clear(t_hash_node **array)
{
	t_hash_node	*tmp_cur;
	t_hash_node	*tmp_prv;

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

int	hasharray_size(t_hash_node *array)
{
	t_hash_node	*tmp;
	int			size;

	if (array == NULL)
		return (0);
	size = 0;
	tmp = array;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
