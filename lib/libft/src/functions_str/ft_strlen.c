/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:14:34 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 13:18:13 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

/*This file contains the function ft_strlen().
 * ft_strlen(const char *str):
 		This function returns the amount of characters 
		in the string pointed to by str.
		If str is a NULL-pointer, then the function returns zero.
		This function expects input according to the standards:
			-a null terminated string
			-a string with no characters after the null terminator
 */

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str != NULL)
	{
		while (*(str + len))
			len++;
	}
	return (len);
}
