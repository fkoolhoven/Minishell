/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                        :+:    :+:             */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 15:00:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/20 15:37:37 by jhendrik      ########   odam.nl         */
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
/*
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
		index = give_hash_index((char *)keys[i], env_table);
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
					terminate_hasharray(head, env_table->size);
					return (-1);
				}
			}
			else
			{
				if (key != NULL)
					free(key);
				if (value != NULL)
					free(value);
				terminate_hasharray(head, env_table->size);
				return (-1);
			}
		}
		else
		{
			terminate_hasharray(head, env_table->size);
			return (-1);
		}
		i++;
	}
	return (0);
}
*/

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

static char	*st_give_key(char *variable)
{
	char	*key;
	char	**split;

	if (variable == NULL)
		return (NULL);
	split = ft_split(variable, '=');
	if (split == NULL)
		return (NULL);
	key = split[0];
	st_free_strarray_i(split, 1);
	return (key);
}

static char	*st_give_value(char *variable)
{
	char	*value;
	char	**split;

	if (variable == NULL)
		return (NULL);
	split = ft_split(variable, '=');
	if (split == NULL)
		return (NULL);
	value = split[1];
	free(split[0]);
	st_free_strarray_i(split, 2);
	return (value);
}

static void	st_error_initkeyvalue(char *key, char *value, t_hash_node ***head, t_hash_table *env_table)
{
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
	terminate_hasharray(head, env_table->size);
}

static int	st_init_add_hashnode(char *key, char *value, t_hash_table *env, t_hash_node ***head)
{
	int			index;
	t_hash_node	*new;

	if (key == NULL || value == NULL || env == NULL || head == NULL)
		return (EXIT_FAILURE);
	if (*head == NULL)
		return (EXIT_FAILURE);
	new = new_hash_node(key, value);
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

static int	st_init_path(char *key, char *value, t_hash_table *env, t_hash_node ***head)
{
	int		check;
	char	*new_value;

	if (key == NULL || value == NULL || env == NULL || head == NULL)
		return (EXIT_FAILURE);
	if (*head == NULL)
		return (EXIT_FAILURE);
	new_value = ft_strjoin("user/test/path:", (const char *)value);
	if (new_value == NULL)
		return (EXIT_FAILURE);
	check = st_init_add_hashnode(key, new_value, env, head);
	if (check == EXIT_FAILURE)
		return (free(new_value), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	st_init_keyvalue_pairs(t_hash_node ***head, t_hash_table *env_table, char **envp)
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
		key = st_give_key(envp[i]);
		value = st_give_value(envp[i]);
		if (key == NULL || value == NULL)
			return (st_error_initkeyvalue(key, value, head, env_table), -2);
		else if (ft_strncmp("PATH", key, ft_strlen(key)) == 0)
		{
			check = st_init_path(key, value, env_table, head);
			if (check == EXIT_FAILURE)
				return (st_error_initkeyvalue(key, value, head, env_table), -2);
		}
		else
		{
			check = st_init_add_hashnode(key, value, env_table, head);
			if (check == EXIT_FAILURE)
				return (st_error_initkeyvalue(key, value, head, env_table), -2);
		}
		i++;
	}
	return (0);
}

t_hash_node	**init_hash_array(t_hash_table *env_table, char **envp)
{
	int			check;
	t_hash_node	**head;

	if (env_table == NULL)
		return (NULL);
	head = hasharray_calloc((env_table->size) + 1, sizeof(t_hash_node *));
	if (head == NULL)
		return (NULL);
	check = st_init_keyvalue_pairs(&head, env_table, envp);
	if (check < 0)
		return (NULL);
	return (head);
}

t_hash_table	*init_env(char **envp)
{
	t_hash_table	*env_table;

	env_table = malloc(sizeof(t_hash_table));
	if (env_table == NULL)
		return (NULL);
	env_table->size = 19;
	env_table->array = init_hash_array(env_table, envp);
	if (env_table->array == NULL)
		return (free(env_table), NULL);
	return (env_table);
}

void	terminate_hashtable(t_hash_table *env_table)
{
	terminate_hasharray(&(env_table->array), env_table->size);
	free(env_table);
}
