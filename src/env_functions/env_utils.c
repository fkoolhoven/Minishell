/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   env_utils.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/20 16:02:22 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/22 12:57:22 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	give_hash_index(char *key, t_htable *env_table)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	if (key == NULL)
		return (-1);
	while (key[i])
	{
		index += (key[i] * (i + 1));
		if (index < 0)
			index = 0;
		i++;
	}
	return (index % (env_table->size));
}

t_hnode	**hasharray_calloc(size_t cnt, size_t size)
{
	t_hnode	**head;
	size_t	i;

	head = malloc(cnt * size);
	if (head == NULL)
		return (NULL);
	i = 0;
	while (i < cnt)
	{
		head[i] = NULL;
		i++;
	}
	return (head);
}

static void	st_free_strarray_i(char **array, int i)
{
	if (array != NULL)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

char	*give_key(char *variable)
{
	char	*key;
	char	**split;

	if (variable == NULL)
		return (NULL);
	split = split_first_occurance(variable, '=');
	if (split == NULL)
		return (NULL);
	key = split[0];
	st_free_strarray_i(split, 1);
	return (key);
}

char	*give_value(char *variable)
{
	char	*value;
	char	**split;

	if (variable == NULL)
		return (NULL);
	split = split_first_occurance(variable, '=');
	if (split == NULL)
		return (NULL);
	value = split[1];
	free(split[0]);
	st_free_strarray_i(split, 2);
	return (value);
}
