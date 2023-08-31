/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 13:40:50 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:03:26 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_striteri().
 * ft_striteri(char *s, void (*f)(unsigned int, char *)):
		This function changes the characters in the string pointed to by s
		by applying the function f on each character of the string 
		passsed as argument, passing its index as first argument.
		If s is NULL, the function does not do anything.
 */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s != NULL)
	{
		i = 0;
		while (*(s + i))
		{
			f(i, (s + i));
			i++;
		}
	}
}
