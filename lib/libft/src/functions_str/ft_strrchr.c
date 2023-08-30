/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 10:55:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:04:46 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions find_chr_rev() and ft_strrchr().
 * find_chr_rev(const char *str, int c):
 		This function searches for the character c in str from end to beginning.
		The function returns a pointer to the character c in str if it is found.
		Otherwise, it returns a NULL-pointer.
 * ft_strrchr(const char *str, int c):
		This function checks whether str is a NULL-pointer.
		If str is a NULL-pointer it returns NULL.
		Otherwise, it calls find_chr_rev() and 
		makes sure it gives an ASCII value based on c.
 */

static char	*find_chr_rev(const char *str, int c)
{
	int	cnt;

	cnt = ft_strlen(str);
	while (cnt >= 0 && *(str + cnt) != c)
		cnt--;
	if (cnt == -1)
		return (NULL);
	if (*(str + cnt) == c)
		return ((char *)(str + cnt));
	return (NULL);
}

char	*ft_strrchr(const char *str, int c)
{
	char	asc_c;

	asc_c = c % 256;
	if (str == NULL)
		return (NULL);
	else
		return (find_chr_rev(str, asc_c));
}
