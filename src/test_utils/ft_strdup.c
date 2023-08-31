/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 15:36:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/31 13:08:49 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

/*This file contains the function ft_strdup().
 * ft_strdup(const char *str):
 		This function makes room for a new string using malloc.
		If malloc fails the function returns a NULL-pointer.
		If str is a NULL-pointer, the function returns a NULL-pointer.
		Otherwise, the function calls ft_strlcpy() to 
		copy str in to the new pointer and returns the new pointer.
 */
static size_t	st_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dst != NULL && src != NULL)
	{
		if (dstsize == 0)
			return (len_src);
		i = 0;
		while (i < (dstsize - 1) && *(src + i))
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (len_src);
}

char	*ft_strdup(const char *str)
{
	char	*ptr_strdup;
	int		len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	ptr_strdup = (char *)malloc(len + 1);
	if (ptr_strdup != NULL)
	{
		st_strlcpy(ptr_strdup, str, len + 1);
		return (ptr_strdup);
	}
	return (NULL);
}
