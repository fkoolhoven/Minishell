/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 10:22:08 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:04:33 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
			if (ft_strncmp(hay + h, ndl, n_len) == 0 && h + n_len - 1 < len)
				return ((char *)(hay + h));
		}
		h++;
	}
	return (NULL);
}
