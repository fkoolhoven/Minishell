/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keyvalue_pairs.c                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:46:06 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/27 10:39:50 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_error(char *key, char *value, t_hnode ***head, t_htable *env)
{
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
	terminate_hasharray(head, env->size);
}

static int	st_add_hnode(char *key, char *value, t_htable *env, t_hnode ***head)
{
	int		index;
	t_hnode	*new;

	if (key == NULL || env == NULL || head == NULL)
		return (EXIT_FAILURE);
	if (*head == NULL)
		return (EXIT_FAILURE);
	new = new_hash_node(key, value); //good
	index = give_hash_index(key, env);
	if (new == NULL || index < 0)
	{
		if (new != NULL)
			hasharray_delone(new);
		return (EXIT_FAILURE);
	}
	hasharray_add_back(&((*head)[index]), new);
	return (EXIT_SUCCESS);
}

static int	st_add_pair(char *key, char *value, t_htable *env, t_hnode ***head)
{
	int	check;

	if (key == NULL || env == NULL || head == NULL)
		return (EXIT_FAILURE);
	if (*head == NULL)
		return (EXIT_FAILURE);
	check = st_add_hnode(key, value, env, head);
	// not freeing here, cause it is freeing afterwards in init_keyvalue()
	if (check == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_keyvalue(t_hnode ***head, t_htable *env_table, char **envp)
{
	int			i;
	int			check;
	char		*key;
	char		*value;

	if (head == NULL || env_table == NULL || envp == NULL)
		return (-1);
	if (*head == NULL)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		key = give_key(envp[i]); // good
		value = give_value(envp[i]); //good
		if (key == NULL)
			return (st_error(key, value, head, env_table), -2);
		else
		{
			check = st_add_pair(key, value, env_table, head);
			if (check == EXIT_FAILURE)
				return (st_error(key, value, head, env_table), -2);
		}
		i++;
	}
	return (0);
}
