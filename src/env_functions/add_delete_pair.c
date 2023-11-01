/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delete_pair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:06:03 by jhendrik          #+#    #+#             */
/*   Updated: 2023/11/01 12:28:22 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hnode	*st_search_prevnode(t_hnode *list, char *key)
{
	t_hnode	*tmp;

	if (list == NULL || key == NULL)
		return (NULL);
	tmp = list;
	if (ft_strncmp(key, tmp->key, ft_strlen(key) + 1) == 0)
		return (NULL);
	while (tmp->next)
	{
		if (ft_strncmp(key, (tmp->next)->key, ft_strlen(key) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_hnode	*st_give_previous(t_htable *env, char *key)
{
	int		index;
	t_hnode	*rtn;

	if (env == NULL || key == NULL)
		return (NULL);
	if (env->array == NULL)
		return (NULL);
	index = give_hash_index(key, env);
	if (index < 0)
		return (NULL);
	rtn = st_search_prevnode((env->array)[index], key);
	return (rtn);
}

int	delete_pair(t_htable *env, char *key)
{
	t_hnode	*to_del;
	t_hnode	*prev;
	t_hnode	*next;
	int		index;

	to_del = find_env_valuenode(env, key);
	index = give_hash_index(key, env);
	if (to_del == NULL || index < 0)
		return (-1);
	next = to_del->next;
	prev = st_give_previous(env, key);
	if (prev == NULL && (env->array)[index] != NULL)
	{
		(env->array)[index] = next;
		to_del->next = NULL;
		hasharray_delone(to_del);
	}
	else
	{
		prev->next = next;
		to_del->next = NULL;
		hasharray_delone(to_del);
	}
	return (0);
}

int	add_pair(t_htable *env, char *key, char *value)
{
	t_hnode	*new;
	int		index;

	if (env == NULL || key == NULL)
		return (-1);
	if (env->array == NULL)
		return (-1);
	new = new_hash_node(key, value);
	index = give_hash_index(key, env);
	if (new == NULL)
		return (-2);
	if (index < 0)
		return (hasharray_delone(new), -2);
	hasharray_add_back(&((env->array)[index]), new);
	return (0);
}
