/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:25:18 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 09:18:49 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

/*
 *This file contains the function ft_bzero(void *str, size_t n).
 *ft_bzero(void *str, size_t n):
		This function checks whether the given pointer is not a NULL-pointer. 
		If the pointer is not a NULL-pointer and n is bigger than zero,
		the function sets everything until n in the pointer to a zero.
	   	This function has no return value.	
 */

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	if (n > 0 && str != NULL)
	{
		i = 0;
		temp = (unsigned char *) str;
		while (i < n)
		{
			*(temp + i) = 0;
			i++;
		}
	}
}
