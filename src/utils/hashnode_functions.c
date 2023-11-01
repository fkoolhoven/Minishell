/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashnode_functions.c                              :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:03:59 by jhendrik          #+#    #+#             */
/*   Updated: 2023/11/01 09:10:16 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hnode	*new_hash_node(char *key, char *value)
{
	t_hnode	*node;

	if (key == NULL)
		return (NULL);
	node = malloc(sizeof(t_hnode)); // good
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_hnode	*hasharray_last(t_hnode *array)
{
	t_hnode	*tmp;

	if (array == NULL)
		return (array);
	tmp = array;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	hasharray_size(t_hnode *array)
{
	t_hnode	*tmp;
	int		size;

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
