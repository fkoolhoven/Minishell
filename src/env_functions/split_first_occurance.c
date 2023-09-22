/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   split_first_occurance.c                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/22 09:38:21 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/22 12:59:56 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	st_decide_size(char const *s, char c)
{
	char	*found;

	if (s == NULL)
		return (1);
	found = ft_strchr((const char *)s, (int)c);
	if (found != NULL)
		return (3);
	else
		return (2);
}

static int	st_give_delindex(char const *s, char c)
{
	int	index;

	if (s == NULL)
		return (0);
	index = 0;
	while (s[index] != c && s[index])
		index++;
	return (index);
}

static void	st_error_malloc(char **split)
{
	if (split[0] != NULL)
		free(split[0]);
	if (split[1] != NULL)
		free(split[1]);
	free(split);
}

static char	**st_fill_strarray(char const *s, char c, char **split, size_t size)
{
	int	del_index;
	int	str_len;

	if (s == NULL || split == NULL)
		return (NULL);
	del_index = st_give_delindex(s, c);
	str_len = ft_strlen((char *)s);
	split[size - 1] = NULL;
	if (size == 2)
	{
		split[0] = (char *)malloc(str_len + 1);
		if (split[0] == NULL)
			return (free(split), NULL);
		ft_strlcpy(split[0], s, str_len + 1);
	}
	else if (size == 3)
	{
		split[0] = (char *)malloc(del_index + 1);
		split[1] = (char *)malloc(str_len - del_index);
		if (split[0] == NULL || split[1] == NULL)
			return (st_error_malloc(split), NULL);
		ft_strlcpy(split[0], s, del_index + 1);
		ft_strlcpy(split[1], (s + del_index + 1), str_len - del_index);
	}
	return (split);
}

char	**split_first_occurance(char const *s, char c)
{
	size_t	size;
	char	**split;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		split = (char **)malloc(1 * sizeof(char *));
		if (split != NULL)
		{
			split[0] = NULL;
			return (split);
		}
		return (NULL);
	}
	size = st_decide_size(s, c);
	split = (char **)malloc(size * sizeof(char *));
	if (split == NULL)
		return (NULL);
	return (st_fill_strarray(s, c, split, size));
}
