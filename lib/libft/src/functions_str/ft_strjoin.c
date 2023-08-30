/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 09:46:46 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:03:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions ft_joining() and ft_strjoin().
 * ft_joining(char const *s1, char const *s2):
 		This function creates a new string using malloc.
		If malloc fails, the function returns a NULL-pointer.
		Otherwise, the function fills the new string with 
		characters in s1, and then with characters in s2.
		It returns the pointer to the new string.
 * ft_strjoin(char const *s1, char const *s2):
 		If s1 and s2 are NULL-pointers, then this function returns a NULL-pointer.
		If s1 is NULL and s2 is not, the function returns s2.
		If s2 is NULL and s1 is not, the function returns s1.
		Otherwise, the function calls ft_joining() to make a new string.
		The function returns the return value of ft_joining().
 */

static char	*ft_joining(char const *s1, char const *s2)
{
	char	*ptr_joi;
	size_t	len_s;
	size_t	i;
	size_t	j;

	len_s = ft_strlen(s1) + ft_strlen(s2);
	ptr_joi = (char *)malloc(len_s + 1);
	if (ptr_joi != NULL)
	{
		i = 0;
		while (*(s1 + i))
		{
			*(ptr_joi + i) = *(s1 + i);
			i++;
		}
		j = 0;
		while (*(s2 + j))
		{
			*(ptr_joi + i + j) = *(s2 + j);
			j++;
		}
		*(ptr_joi + i + j) = '\0';
		return (ptr_joi);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	return (ft_joining(s1, s2));
}
