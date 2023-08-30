/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 11:01:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:04:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions:
 			-lr_c_inset()
			-rl_c_inset()
			-ft_help_ends()
			-ft_help_else()
			-ft_strtrim()
 * lr_c_inset(char const *s1, char const *set):
 		This function checks from left to right (beginning to end)
		if the characters in s1 coincide with characters in set.
		This function returns the index of the first character 
		in s1 which does not coincide with a character in set. 
		If all characters in s1 coincide with a character in set,
		the function returns the length of s1.
		If s1 or set is a NULL-pointer, this function will crash.
 * rl_c_inset(char const *s1, char const *set):
 		This function checks from right to left (end to beginning)
		if the characters in s1 coincide with characters in set.
		It does this the same way as lr_c_inset().
		If s1 is a string containing only the null-terminator,
		the function returns -1.
		The difference is that when all the characters in s1
		match a character in set, the function returns zero.
 * ft_help_ends(void):
 		This function creates a string using malloc 
		with place for one character.
		If the malloc fails, the function returns NULL.
		Otherwise, the function fills the new string with a 
		null-terminator and returns the pointer to this string.
 * ft_help_else(char const *s1, int begin, int end):
 		This function creates a new string using malloc.
		If malloc fails, the function returns a NULL-pointer.
		Otherwise, the function fills the new string with 
		characters in s1 from (begin+1) to end and null-terminates it.
		The pointer to the new string is returned.
		Instead of this function, the function ft_substr() could
		have been used.
 * ft_strtrim(char const *s1, char const *set):
 		This function returns a copy of the string pointed to by 
		s1 which does not contain the characters in the string
		pointed to by set from the beginning and the end.
		If s1 and set are NULL or s1 is NULL, the function returns NULL.
		If set is NULL and s1 is not, the function returns s1.
		Otherwise, the function determines which part of s1 should be copied
		by determining the beginning and the end by calling lr_c_inset() and
		rl_c_inset().
		If s1 consists of only characters in set, the function returns a string
		containing only a null-terminator by calling ft_help_ends().
		Otherwise, the function calls ft_help_else() to create 
		a new string and copy the proper part of s1 in to the new string and
		return the return value of ft_help_else() (the pointer to the new string).
 */

static int	lr_c_inset(char const *s1, char const *set)
{
	int		i;
	char	*inset;

	i = 0;
	inset = ft_strchr(set, *s1);
	while (*(s1 + i) && (inset != NULL))
	{
		i++;
		inset = ft_strchr(set, *(s1 + i));
	}
	return (i);
}

static int	rl_c_inset(char const *s1, char const *set)
{
	int		j;
	char	*inset;

	j = ft_strlen(s1) - 1;
	if (j < 0)
		return (-1);
	inset = ft_strchr(set, *(s1 + j));
	while (j > 0 && (inset != NULL))
	{
		j--;
		inset = ft_strchr(set, *(s1 + j));
	}
	return (j);
}

static char	*ft_help_ends(void)
{
	char	*ptr_trim;

	ptr_trim = (char *)malloc(1);
	if (ptr_trim != NULL)
	{
		ptr_trim[0] = '\0';
		return (ptr_trim);
	}
	return (NULL);
}

static char	*ft_help_else(char const *s1, int begin, int end)
{
	char	*ptr_trim;
	int		i;

	i = 0;
	ptr_trim = (char *)malloc(end - begin + 2);
	if (ptr_trim == NULL)
		return (NULL);
	while ((begin + i) <= end)
	{
		*(ptr_trim + i) = *(s1 + begin + i);
		i++;
	}
	*(ptr_trim + i) = '\0';
	return (ptr_trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	begin;
	int	end;
	int	len;

	if ((s1 == NULL && set == NULL) || s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	len = ft_strlen(s1);
	begin = lr_c_inset(s1, set);
	end = rl_c_inset(s1, set);
	if ((end == 0 && begin == len) || end == -1)
		return (ft_help_ends());
	return (ft_help_else(s1, begin, end));
}
