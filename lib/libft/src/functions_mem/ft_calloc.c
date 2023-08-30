/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 15:06:33 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/18 09:49:39 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

/*
 *This file contains the functions:
 			- check_max(size_t cnt, size_t size)
			- ft_calloc(size_t cnt, size_t size)
 *check_max(size_t cnt, size_t size):
 			This function checks whether the input 
			doesn't exceed the maximum value of size_t.
			When the maximum value is exceded the 
			function returns one. 
			Otherwise it returns zero.
 *ft_calloc(size_t cnt, size_t size):
 			This function allocates memory of size * cnt using malloc,
			and fills the allocated memory with NULL.
			If malloc fails, or the size * cnt exceeds 
			the maximum value of size_t,
			then the function returns a NULL-pointer.
 */

static int	check_max(size_t cnt, size_t size)
{
	size_t					max;
	unsigned long long int	len;

	len = (unsigned long long int)(cnt * size);
	max = (size_t)-1;
	if (len > max)
		return (1);
	if (cnt > 42949967295 && size > 42949967295)
		return (1);
	return (0);
}

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*ptr;
	char	*ptr_cp;
	size_t	i;
	size_t	len;

	if (check_max(cnt, size) == 0)
	{
		len = cnt * size;
		ptr = malloc(len);
		if (ptr != NULL)
		{
			ptr_cp = (char *)ptr;
			i = 0;
			while (i < len)
			{
				*(ptr_cp + i) = 0;
				i++;
			}
			return (ptr);
		}
		return (NULL);
	}
	return (NULL);
}
