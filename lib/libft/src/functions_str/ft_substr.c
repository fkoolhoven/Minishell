/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 16:04:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:05:07 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions ft_lenzero(), ft_endblen() and ft_substr().
 * ft_lenzero(void):
 		This function creates a new string using malloc.
		If the malloc does not fail, this string contains one character
	   	which is the NULL-terminator and the function 
		returns the pointer to this string.
		Otherwise, the function returns a NULL-pointer.

 * ft_endblen(char const *s, unsigned int start, unsigned int len_s):
 		This function creates a new string using malloc.
		If malloc fails, the function returns a NULL-pointer.
		Otherwise, the function calls ft_strlcpy() to copy 
		the string pointed to by s, from start until (start+len) 
		(adding one to ensure null-termination) and 
		returns the pointer to the new string.
 * ft_substr(char const *s, unsigned int start, size_t len):
 		This function creates a new string using malloc, 
		containing the characters in s from start until (start+len).
		If s is a NULL-pointer the function returns a NULL-pointer. 
		If start lies outside the string pointed to by s, or
		len is zero, or the lenght of s is zero, the function returns
		a pointer to a string containing only the null-terminator,
		by calling the function ft_lenzero().
		If (start+len) lies outside the string pointed to by s,
		the function copies everything from start until the end 
		of s in to a new string and returns the pointer to this string.
		If (start+len) lies within the string pointed to by s,
		the function copies everything from start until (start+len)
		of s in to a new string and returns the pointer to this string.
 */

static char	*ft_lenzero(void)
{
	char	*ptr_sub;

	ptr_sub = (char *)malloc(1);
	if (ptr_sub != NULL)
	{
		ptr_sub[0] = '\0';
		return (ptr_sub);
	}
	return (NULL);
}

static char	*ft_endblen(char const *s, unsigned int start, unsigned int len_s)
{
	char	*ptr_sub;

	ptr_sub = (char *)malloc(len_s - start + 1);
	if (ptr_sub != NULL)
	{
		ft_strlcpy(ptr_sub, (s + start), (len_s - start + 1));
		return (ptr_sub);
	}
	return (NULL);
}

static char	*ft_endslen(char const *s, unsigned int start, size_t len)
{
	char	*ptr_sub;

	ptr_sub = (char *)malloc(len + 1);
	if (ptr_sub != NULL)
	{
		ft_strlcpy(ptr_sub, (s + start), len + 1);
		return (ptr_sub);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	len_s = (unsigned int)ft_strlen(s);
	if (start > len_s || len == 0 || len_s == 0)
		return (ft_lenzero());
	end = start + (unsigned int)len;
	if (end > len_s)
		return (ft_endblen(s, start, len_s));
	else
		return (ft_endslen(s, start, len));
}
