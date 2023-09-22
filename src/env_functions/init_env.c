/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_env.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/20 16:01:17 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/22 12:57:47 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_hnode	**init_hash_array(t_htable *env_table, char **envp)
{
	int		check;
	t_hnode	**head;

	if (env_table == NULL)
		return (NULL);
	head = hasharray_calloc((env_table->size) + 1, sizeof(t_hnode *));
	if (head == NULL)
		return (NULL);
	check = init_keyvalue(&head, env_table, envp);
	if (check < 0)
		return (NULL);
	return (head);
}

t_htable	*init_env(char **envp)
{
	t_htable	*env_table;

	env_table = malloc(sizeof(t_htable));
	if (env_table == NULL)
		return (NULL);
	env_table->size = 19;
	env_table->array = init_hash_array(env_table, envp);
	if (env_table->array == NULL)
		return (free(env_table), NULL);
	return (env_table);
}
