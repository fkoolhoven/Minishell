/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:17:09 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:06:39 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_memchr().
 * ft_memchr(const void *str, int c, size_t n):
 		If str is a NULL-pointer the function returns NULL.
		Otherwise, the function searches n bytes for 
		the character c in str byte by byte.
		If the function found the character c, 
		it returns the pointer to the character in str.
		This function is not protected against overflow.
 */

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	c_uchr;
	unsigned char	*temp_str;
	size_t			cnt;

	c_uchr = (unsigned char) c;
	if (str != NULL)
	{
		temp_str = (unsigned char *) str;
		cnt = 0;
		while (cnt < n && ((*(temp_str + cnt)) != c_uchr))
			cnt++;
		if (cnt == n)
			return (NULL);
		return ((void *)(str + cnt));
	}
	return (NULL);
}
