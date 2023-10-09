/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:11:51 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/09 16:45:03 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_hashnode(t_hnode *node, t_htable *env)
{
	int	index;

	if (node == NULL)
		printf("(NULL)\n");
	else
	{
		index = give_hash_index(node->key, env);
		printf("This node has index %i\n", index);
		printf("Node own pointer: %p \n \t key: %s \n \t value: %s \n \t next: %p \n", node, node->key, node->value, node->next);
	}
}

static void	st_print_hashnodes(t_hnode *head)
{
	t_hnode *tmp;

	if (head == NULL)
		printf("(NULL)\n");
	else
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->key[0] == 'X')
				printf("Node own pointer: %p \n \t key: %s \n \t value: %s \n \t next: %p \n", tmp, tmp->key, tmp->value, tmp->next);
			tmp = tmp->next;
		}
	}
}

void	print_hasharray(t_htable *env_table, t_hnode **head)
{
	int	i;

	printf("Printing hash array for env \n");
	if (head == NULL)
		printf("(NULL)\n");
	else
	{
		i = 0;
		while (i < (env_table->size))
		{
			printf("Index: %i\n", i);
			st_print_hashnodes((head)[i]);
			i++;
		}
	}
}

void	print_hashtable(t_htable *env_table)
{

	printf("Printing hash table\n");
	if (env_table == NULL)
		printf("(NULL)\n");
	else
	{
		printf("Size: %i\n", env_table->size);
		printf("Hash array\n");
		print_hasharray(env_table, env_table->array);
	}
}

void	print_strarray(char **envp)
{
	int	i;

	printf("PRINTING environment var of shell\n");
	if (envp == NULL)
		printf("(NULL)\n");
	else
	{
		i = 0;
		while (envp[i])
		{
			printf("%s", envp[i]);
			printf("\n");
			i++;
		}
	}
}

static int	st_comparing(char *env, char **new_env)
{
	int	j;

	j = 0;
	while (new_env[j])
	{
		if (ft_strncmp(env, new_env[j], ft_strlen(env)) == 0)
			return (0);
		j++;
	}
	return (1);
}

int	comparing_envs(char **env, char **new_env)
{
	int	i;
	int	j;

	if (env != NULL && new_env != NULL)
	{
		i = 0;
		while (env[i])
		{
			j = st_comparing(env[i], new_env);
			if (j == 1)
				return (1);
			i++;
		}
		return (0);
	}
	return (-1);
}
