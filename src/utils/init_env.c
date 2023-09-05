/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 15:00:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/05 16:53:48 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	give_hash_index(char *key, t_hash_table *env_table)
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

t_hash_node	**hasharray_calloc(size_t cnt, size_t size)
{
	t_hash_node	**head;
	size_t		i;

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

void	terminate_hasharray(t_hash_node ***head, int size)
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

static int	st_init_keyvalue_pairs(t_hash_node ***head, const char **keys, const char **values, t_hash_table *env_table)
{
	t_hash_node	*new;
	int	i;
	int	index;
	char	*key;
	char	*value;

	i = 0;
	while (keys[i] != NULL)
	{
		index = give_hash_index(keys[i], env_table);
		if (index >= 0)
		{
			key = ft_strdup(keys[i]);
			value = ft_strdup(values[i]);
			if (key != NULL && value != NULL)
			{
				new = new_hash_node(key, value);
				if (new != NULL)
					hasharray_add_back(&((*head)[index]), new);
				else
				{
					free(key);
					free(value);
					terminate_hasharray(head);
					return (-1);
				}
			}
			else
			{
				if (key != NULL)
					free(key);
				if (value != NULL)
					free(value);
				terminate_hasharray(head);
				return (-1);
			}
		}
		else
		{
			terminate_hasharray(head);
			return (-1);
		}
	}
	return (0);
}

t_hash_node	**init_hash_array(t_hash_table *env_table)
{
	int			check;
	t_hash_node	**head;
	const char **keys={"USER",
	"PATH",
	"PWD",
	"HOME",
	"LOGNAME",
	NULL};
	const char	**values={"alien",
	"/Users/alien",
	"Current directory",
	"/Users/alien",
	"jean_the_alien"};

	if (env_table == NULL)
		return (NULL);
	head = hasharray_calloc((env_table->size) + 1, sizeof(t_hash_node *));
	if (head == NULL)
		return (NULL);
	check = st_init_keyvalue_pairs(&head, keys, values, env_table);
	if (check < 0)
		return (NULL);
	return (head);
}

t_hash_table	*init_env()
{
	t_hash_table	*env_table;

	env_table = malloc(sizeof(t_hash_table));
	if (env_table == NULL)
		return (NULL);
	env_table->size = 29;
	init_hash_array(env_table);
	
}

void	terminate_hashtable(t_hash_table *env_table)
{
	terminate_hasharray(&(env_table->array));
	free(env_table);
}
