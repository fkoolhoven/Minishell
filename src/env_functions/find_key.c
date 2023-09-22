/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   find_key.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/20 16:53:05 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/22 14:59:35 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*st_search_key(t_hnode *list, char *key)
{
	t_hnode	*tmp;

	if (list == NULL || key == NULL)
		return (NULL);
	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*st_find_newkey(t_htable *env, char *key)
{
	int		index;
	char	*rtn;
	char	*new_key;

	new_key = ft_strdup(key + 1);
	if (new_key != NULL)
	{
		index = give_hash_index(new_key, env);
		if (index < 0)
			return (NULL);
		rtn = st_search_key((env->array)[index], new_key);
		free(new_key);
		return (rtn);
	}
	else
		return (NULL);
}

char	*find_env_value(t_htable *env, char *key)
{
	int		index;
	char	*rtn;

	if (env == NULL || key == NULL)
		return (NULL);
	if (env->array == NULL)
		return (NULL);
	if (key[0] == '$')
		return (st_find_newkey(env, key));
	else
	{
		index = give_hash_index(key, env);
		if (index < 0)
			return (NULL);
		return (st_search_key((env->array)[index], key));
	}
}

static t_hnode	*st_search_node(t_hnode *list, char *key)
{
	t_hnode	*tmp;

	if (list == NULL || key == NULL)
		return (NULL);
	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_hnode	*find_env_valuenode(t_htable *env, char *key)
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
	rtn = st_search_node((env->array)[index], key);
	return (rtn);
}
