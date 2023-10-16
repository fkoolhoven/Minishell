/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_strtrim.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/16 15:59:04 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/16 17:08:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


static int	lr_c_inset(char const *s1, char const *set)
{
	int		i;
	char	*inset;

	i = 0;
	inset = ft_strchr(set, *s1);
	while (*(s1 + i) && (inset != NULL))
	{
		i++;
		inset = ft_strchr(set, *(s1 + i));
	}
	if (i > 0)
		return (i - 1);
	return (i);
}

static int	rl_c_inset(char const *s1, char const *set)
{
	int		j;
	char	*inset;

	j = ft_strlen(s1) - 1;
	if (j < 0)
		return (-1);
	inset = ft_strchr(set, *(s1 + j));
	while (j > 0 && (inset != NULL))
	{
		j--;
		inset = ft_strchr(set, *(s1 + j));
	}
	return (j);
}

static char	*st_nothing_left(void)
{
	char	*ptr_trim;

	ptr_trim = (char *)malloc(1);
	if (ptr_trim != NULL)
	{
		ptr_trim[0] = '\0';
		return (ptr_trim);
	}
	return (NULL);
}

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

static size_t	st_len_trim_between(char *s1, char const *set)
{
	int		i;
	size_t	len;
	char	*inset1;
	char	*inset2;

	i = 0;
	len = 0;
	while (*(s1 + i))
	{
		inset1 = ft_strchr(set, *(s1 + i));
		if (i > 0)
			inset2 = ft_strchr(set, *(s1 + i - 1));
		else
			inset2 = NULL;
		if (inset1 == NULL)
			len++;
		if (inset1 != NULL && inset2 == NULL)
			len++;
		i++;
	}
	return (len);
}

static char	*st_trim_between(char *str, char const *set, size_t len)
{
	int		i;
	size_t	j;
	char	*trimmed;
	char	*inset1;
	char	*inset2;

	if (len < 0 || set == NULL || str == NULL)
		return (free(str), NULL);
	trimmed = (char *)malloc(len + 1);
	if (trimmed == NULL)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i] && j < len)
	{
		inset1 = ft_strchr(set, str[i]);
		if (i > 0)
			inset2 = ft_strchr(set, str[i - 1]);
		else
			inset2 = NULL;
		if (inset1 == NULL)
		{
			trimmed[j] = str[i];
			j++;
		}
		if (inset1 != NULL && inset2 == NULL)
		{
			trimmed[j] = str[i];
			j++;
		}
		i++;
	}
	trimmed[j] = '\0';
	return (free(str), trimmed);
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
	begin = lr_c_inset(s1, set);
	end = rl_c_inset(s1, set);
	if ((end == 0 && ((size_t)begin) == len) || end == -1)
		return (st_nothing_left());
	str_trim = st_trim_be(s1, begin, end);
	if (str_trim == NULL)
		return (NULL);
	len = st_len_trim_between(str_trim, set);
	if (len == ft_strlen(str_trim))
		return (str_trim);
	return (st_trim_between(str_trim, set, len));
}
