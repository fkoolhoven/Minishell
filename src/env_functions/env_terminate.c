/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   env_terminate.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/20 15:44:29 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/20 16:42:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	terminate_hasharray(t_hnode ***head, int size)
{
	int	i;

	if (head != NULL)
	{
		if (*head != NULL)
		{
			i = 0;
			while (i < size)
			{
				hasharray_clear(&((*head)[i]));
				i++;
			}
			free(*head);
			*head = NULL;
		}
	}
}

void	terminate_hashtable(t_htable *env_table)
{
	terminate_hasharray(&(env_table->array), env_table->size);
	free(env_table);
}
