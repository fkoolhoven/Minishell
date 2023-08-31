/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 10:21:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:06:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions: 
			- ft_dst_s_src()
			- ft_dst_b_src()
			- ft_memmove()
 * ft_dst_s_src(void *dst, const void *src, size_t n):
 		This function moves n bytes of src in to dst
		starting from the beginning to the end of src and dst. 
		This function expects that n is smaller or equal to
		the size of dst and src, and that dst and 
		src are not NULL-pointers.
		If the input is not as described above, 
		the function has undefined behavior.
		This function returns dst.

 * ft_dst_b_src(void *dst, const void *src, size_t n):
 		This function moves n bytes of src in to dst 
		starting from the end to the beginning of src and dst. 
		This function expects that n is smaller or equal to 
		the size of dst and src, and that dst and 
		src are not NULL-pointers.
		If the input is not as described above, 
		the function has undefined behavior.
		This function returns dst.

 * ft_memmove(void *dst, const void *src, size_t n):
 		This function moves n bytes of src in to dst.
		How this is done depends on whether src is bigger than dst, 
		or not.
		This is important if the containers overlap, 
		because if they overlap the content in src might be lost 
		if you copy from beginning to end or the otherway around. 
		This function returns a NULL-pointer if dst or 
		src is a NULL-pointer.
		Otherwise, the function returns dst.
		If n is bigger than the size of dst or src, 
		this function has undefined behavior.
 */

static void	*ft_dst_s_src(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		i;

	ptr_dst = (char *)dst;
	ptr_src = (const char *)src;
	i = 0;
	while (i < n)
	{
		*(ptr_dst + i) = *(ptr_src + i);
		i++;
	}
	return (dst);
}

static void	*ft_dst_b_src(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		i;

	ptr_dst = (char *)dst;
	ptr_src = (const char *)src;
	i = n;
	while (i >= 1)
	{
		*(ptr_dst + i - 1) = *(ptr_src + i - 1);
		i--;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (dst == NULL || src == NULL)
		return (NULL);
	if (dst <= src)
		return (ft_dst_s_src(dst, src, n));
	return (ft_dst_b_src(dst, src, n));
}
