/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:27:13 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:03:09 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_strlcat().
 * ft_strlcat(char *dst, const char *src, size_t dstsize):
 		This function concatenates the strings dst and src in dst.
		It concatenates as much as possible according to dstsize.
		If length of dst is bigger than or equal to dstsize, 
		nothing is added to dst and an integer is returned.
		If length of dst is smaller than dstsize, 
		(dstsize - length of dst - 1) characters of src are added to dst.
		If dst or src are NULL-pointers, nothing is added and an integer is returned.
 */

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_i;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dst == NULL)
		return (src_len);
	dst_i = 0;
	while (*(dst + dst_i) && dst_i < dstsize)
		dst_i++;
	if (dst_i == dstsize || src == NULL)
		return (dstsize + src_len);
	i = 0;
	while (i < (dstsize - dst_i - 1) && *(src + i))
	{
		*(dst + dst_i + i) = *(src + i);
		i++;
	}
	*(dst + dst_i + i) = '\0';
	return (dst_i + src_len);
}
