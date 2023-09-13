/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 16:54:34 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/13 11:30:47 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	st_print_hashnodes(t_hash_node *head)
{
	t_hash_node *tmp;

	if (head == NULL)
		printf("(NULL)\n");
	else
	{
		tmp = head;
		while (tmp)
		{
			printf("Node own pointer: %p \n \t key: %s \n \t value: %s \n \t next: %p \n", tmp, tmp->key, tmp->value, tmp->next);
			tmp = tmp->next;
		}
	}
}

static void	st_print_hasharray(t_hash_table *env_table)
{
	int	i;

	printf("Printing hash array for env \n");
	if (env_table->array == NULL)
		printf("(NULL)\n");
	else
	{
		i = 0;
		while (i < (env_table->size))
		{
			printf("Index: %i\n", i);
			st_print_hashnodes((env_table->array)[i]);
			i++;
		}
	}
}

static void	st_print_hashtable(t_hash_table *env_table)
{
	printf("Printing hash table for env \n");
	if (env_table == NULL)
		printf("(NULL)\n");
	else
	{
		printf("Size: %i\n", env_table->size);
		st_print_hasharray(env_table);
	}
}

int	main(void)
{
	t_hash_table	*env;

	env = init_env();
	st_print_hashtable(env);
	terminate_hashtable(env);
	return (0);
}
