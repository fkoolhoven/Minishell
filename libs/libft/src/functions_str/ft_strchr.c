/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 10:29:29 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:03:46 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions find_chr(), ft_strchr().
 * find_chr(const char *str, int c):
 		This function searches for c character by character 
		in the string pointed to by str.
		If c is found in str, the function returns 
		the pointer to the character in str.
		Otherwise, the function returns a NULL-pointer.
		This function is not protected against overflow.
 * ft_strchr(const char *str, int c):
 		This function checks whether the str 
		is a NULL-pointer or not.
		If str is a NULL-pointer, it returns a NULL-pointer.
		Otherwise, it makes sure that an ASCII value is 
		given to the function find_chr() and 
		returns the return value of find_chr().
		This function is not protected against overflow.
 */

static char	*find_chr(const char *str, int c)
{
	int	cnt;

	cnt = 0;
	while (*(str + cnt) && (*(str + cnt) != c))
		cnt++;
	if (*(str + cnt) == c)
		return ((char *)(str + cnt));
	return (NULL);
}

char	*ft_strchr(const char *str, int c)
{
	char	asc_c;

	asc_c = c % 256;
	if (str == NULL)
		return (NULL);
	else
		return (find_chr(str, asc_c));
}
