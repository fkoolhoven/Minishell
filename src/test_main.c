/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 16:54:34 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/20 15:23:46 by jhendrik      ########   odam.nl         */
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

void	print_hasharray(t_hash_table *env_table, t_hash_node **head)
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

void	print_hashtable(t_hash_table *env_table)
{
	printf("Printing hash table for env \n");
	if (env_table == NULL)
		printf("(NULL)\n");
	else
	{
		printf("Size: %i\n", env_table->size);
		print_hasharray(env_table, env_table->array);
	}
}

static void	st_print_env(char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	t_hash_table	*env;

	if (argc < 1 || argv == NULL)
		return (EXIT_FAILURE);
	printf("HELLO I'm in main\n");
	st_print_env(envp);
	env = init_env(envp);
	print_hashtable(env);
	terminate_hashtable(env);
	return (0);
}
