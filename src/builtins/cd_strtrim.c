/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_strtrim.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:37:29 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/30 17:58:22 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*st_trim_be(char const *s1, int begin, int end)
{
	char	*ptr_trim;
	int		i;

	i = 0;
	ptr_trim = (char *)malloc(end - begin + 2);
	if (ptr_trim == NULL)
		return (NULL);
	while ((begin + i) <= end)
	{
		*(ptr_trim + i) = *(s1 + begin + i);
		i++;
	}
	*(ptr_trim + i) = '\0';
	return (ptr_trim);
}

static void	st_add_chr(t_trim_var *trim, size_t i)
{
	if (trim != NULL)
	{
		if (trim->inset1 == NULL)
		{
			trim->trimmed[trim->j] = trim->str[i];
			(trim->j)++;
		}
		if (trim->inset1 != NULL && trim->inset2 == NULL)
		{
			trim->trimmed[trim->j] = trim->str[i];
			(trim->j)++;
		}
	}
}

static char	*st_trim_between(char *str, char const *set, size_t len)
{
	size_t		i;
	t_trim_var	trim;

	if (len < 0 || set == NULL || str == NULL)
		return (free(str), NULL);
	trim.trimmed = (char *)malloc(len + 1);
	if (trim.trimmed == NULL)
		return (free(str), NULL);
	trim.str = str;
	i = 0;
	trim.j = 0;
	while (str[i] && trim.j < len)
	{
		trim.inset1 = ft_strchr(set, str[i]);
		if (i > 0)
			trim.inset2 = ft_strchr(set, str[i - 1]);
		else
			trim.inset2 = NULL;
		st_add_chr(&trim, i);
		i++;
	}
	trim.trimmed[trim.j] = '\0';
	return (free(str), trim.trimmed);
}

char	*cd_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	size_t	len;
	char	*str_trim;

	if ((s1 == NULL && set == NULL) || s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	len = ft_strlen(s1);
	begin = cd_lr_c_inset(s1, set);
	end = cd_rl_c_inset(s1, set);
	if ((end == 0 && ((size_t)begin) == len) || end == -1)
		return (NULL);
	str_trim = st_trim_be(s1, begin, end);
	if (str_trim == NULL)
		return (NULL);
	len = cd_len_trim_between(str_trim, set);
	if (len == ft_strlen(str_trim))
		return (str_trim);
	return (st_trim_between(str_trim, set, len));
}
