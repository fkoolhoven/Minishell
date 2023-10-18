/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_strtrim_utils.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:37:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/18 15:38:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_lr_c_inset(char const *s1, char const *set)
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

int	cd_rl_c_inset(char const *s1, char const *set)
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

char	*cd_nothing_left(void)
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

size_t	cd_len_trim_between(char *s1, char const *set)
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
