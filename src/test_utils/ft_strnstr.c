/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 10:22:08 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/30 17:17:15 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

/*This file contains ft_strnstr().
 * ft_strnstr(const char *hay, const char *ndl, size_t len):
 		This function looks for the string ndl 
		in the string hay for len bytes.
		It accomplishes this by first searching for the 
		first character of ndl in hay and 
		then calling ft_strncmp() to check if the rest is the same.
		If hay and ndl are NULL, it returns NULL.
		If the length of ndl is zero, it returns hay.
		If ndl is NULL, it returns hay, because ft_strlen() will return zero.
		If ndl is not found in hay, it returns NULL.
 */
static int	comparing(const char *s1, const char *s2, size_t n)
{
	size_t			cnt;
	unsigned char	c_s1;
	unsigned char	c_s2;

	cnt = 0;
	c_s1 = (unsigned char)(*(s1 + cnt));
	c_s2 = (unsigned char)(*(s2 + cnt));
	while (c_s1 && c_s2 && (cnt < n))
	{
		if (c_s1 != c_s2)
			return (c_s1 - c_s2);
		cnt++;
		c_s1 = (unsigned char)(*(s1 + cnt));
		c_s2 = (unsigned char)(*(s2 + cnt));
	}
	if (cnt == 0 && n == 0)
		return (0);
	if (cnt == n)
	{
		c_s1 = (unsigned char)(*(s1 + cnt - 1));
		c_s2 = (unsigned char)(*(s2 + cnt - 1));
		return (c_s1 - c_s2);
	}
	return (c_s1 - c_s2);
}

static int	st_strncmp(const char *s1, const char *s2, size_t n)
{
	return (comparing(s1, s2, n));
}

char	*ft_strnstr(const char *hay, const char *ndl, size_t len)
{
	size_t	h;
	size_t	n_len;

	if (hay == NULL && ndl == NULL)
		return (NULL);
	h = 0;
	n_len = ft_strlen(ndl);
	if (n_len == 0)
		return ((char *)hay);
	while (*(hay + h) && h < len)
	{
		if (*(hay + h) == *ndl)
		{
			if (st_strncmp(hay + h, ndl, n_len) == 0 && h + n_len - 1 < len)
				return ((char *)(hay + h));
		}
		h++;
	}
	return (NULL);
}
