/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   convert_to_strarray.c                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/22 11:45:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 13:30:59 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	st_add_per_index(t_hnode *head, char **ch_env, int *index)
{
	char	*tmp_str;
	t_hnode	*tmp;

	if (head == NULL)
		return (0);
	if (index == NULL)
		return (-1);
	if (*index < 0)
		return (-1);
	tmp = head;
	while (tmp)
	{
		tmp_str = give_envstr(tmp);
		if (tmp_str == NULL)
			return (-2);
		ch_env[(*index)] = tmp_str;
		tmp = tmp->next;
		(*index) += 1;
	}
	return (0);
}

static void	st_error(char **ch_env, int index)
{
	int	i;

	if (ch_env != NULL)
	{
		i = 0;
		while (i < index)
		{
			free(ch_env[i]);
			i++;
		}
		free(ch_env);
	}
}

static char	**st_fill_strarray(t_htable *env, char **ch_env, int size)
{
	t_hnode	**array;
	int		i;
	int		j;
	int		check;

	if (env == NULL || ch_env == NULL)
		return (st_error(ch_env, 0), NULL);
	array = env->array;
	if (array == NULL)
		return (st_error(ch_env, 0), NULL);
	i = 0;
	j = 0;
	ch_env[size] = NULL;
	while (i < env->size)
	{
		check = st_add_per_index(array[i], ch_env, &j);
		if (check < 0)
			return (st_error(ch_env, j), NULL);
		i++;
	}
	return (ch_env);
}

char	**convert_htable_to_strarray(t_htable *env)
{
	char	**ch_env;
	int		size;

	if (env == NULL)
		return (NULL);
	size = size_table(env);
	if (size == 0)
		return (st_error(NULL, 0), NULL);
	ch_env = malloc((size + 1) * sizeof(char *));
	if (ch_env == NULL)
		return (st_error(ch_env, 0), NULL);
	return (st_fill_strarray(env, ch_env, size));
}
