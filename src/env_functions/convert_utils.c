/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:02:07 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/09 17:00:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_size_at_index(t_hnode *head, int *size)
{
	t_hnode	*tmp;

	if (size != NULL)
	{
		if (head != NULL)
		{
			tmp = head;
			while (tmp)
			{
				(*size) += 1;
				tmp = tmp->next;
			}
		}
	}
}

int	size_table(t_htable *env)
{
	int		size;
	int		i;
	t_hnode	**array;

	if (env == NULL)
		return (0);
	i = 0;
	size = 0;
	array = env->array;
	if (array == NULL)
		return (0);
	while (i < env->size)
	{
		st_size_at_index(array[i], &size);
		i++;
	}
	return (size);
}

char	*give_envstr(t_hnode *node)
{
	char	*tmp1;
	char	*tmp2;

	if (node == NULL)
		return (NULL);
	tmp1 = ft_strjoin(node->key, "=");
	if (tmp1 == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, node->value);
	if (tmp1 != tmp2)
		free(tmp1);
	if (tmp2 == NULL)
		return (NULL);
	return (tmp2);
}
