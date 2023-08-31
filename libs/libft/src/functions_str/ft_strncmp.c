/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 11:21:38 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:04:23 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions comparing() and ft_strncmp().
 * comparing(const char *s1, const char *s2, size_t n):
 		This function compares the strings s1 and s2 character by character.
		It returns the difference in ASCII value between the characters.
		If nothing is compared because n=0, it returns zero.
		This function is not protected against overflow.
		This function expects that s1 and s2 are not NULL-pointers.
 * ft_strncmp(const char *s1, const char *s2, size_t n):
 		This function checks whether s1 or s2 is a NULL-pointer.
		If s1 or s2 is NULL, this function will segfault.
		Otherwise, it calls comparing() and returns its return value.
		This function is not protected against overflow.
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	return (comparing(s1, s2, n));
}
