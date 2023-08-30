/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 12:32:06 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:07:07 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_memset().
 *ft_memset(void *b, int c, size_t len):
 		This function fills the given memory, pointed to by b, 
		until len bytes with the given ASCII value c.
		If b is a NULL-pointer, 
		the function returns b without changing the contents.
 */

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	if (b != NULL)
	{
		temp = b;
		i = 0;
		while (i < len)
		{
			*(temp + i) = (unsigned char) c;
			i++;
		}
	}
	return (b);
}
