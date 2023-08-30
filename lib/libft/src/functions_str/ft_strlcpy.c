/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:57:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:02:45 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_strlcpy().
 * ft_strlcpy(char *dst, const char *src, size_t dstsize):
 		This function copies (dstsize - 1) bytes of the string 
		pointed to by src in to the string pointed to by dst, 
		and null terminates the string pointed to by dst. 
		This function assumes that the string pointed to by src
		is a proper string (null terminated and nothing after the null-terminator),
		and that dstsize is smaller than or equal to the size available in the string
		pointed to by dst. Any improper input gives undefined behavior.
		If dst and src overlap, this function gives undefined behavior.
		If dst or src is a NULL-pointer, the function returns the length of src.
		The length of src if src is a NULL-pointer will be zero 
		(check the implementation of the function ft_strlen()).
		This function always returns the length of 
		the total string it tried to create.
 */

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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
