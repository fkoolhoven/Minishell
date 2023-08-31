/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_luitoa_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 12:41:07 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:09:44 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions:
			- ft_nblen()
			- ft_luitoa_base().
 *ft_nblen(long unsigned int n, int base):
 		This function returns the amount of digits n consists 
		of if it is displayed in the given base.
 *ft_luitoa_base(long unsigned int n, int base, char *base_str):
 		This function converts the given n to a string. 
		The given n will be converted in the given base as 
		given in the base string pointed to by base_str.
		The memory for the new string is allocated 
		with malloc by calling ft_calloc().
		If the malloc fails, the functions returns a NULL-pointer.
		If an invalid base or a base string has a length 
		not equal to base, the function will return a NULL-pointer.
		If base_str is a NULL-pointer, 
		the function returns a NULL-pointer.
		Otherwise, the function returns the new string.
		This function only gives correct output if 
		n is given in base ten representation.
 */

static int	ft_nblen(long unsigned int n, int base)
{
	long unsigned int	i;
	long unsigned int	cnt;
	long unsigned int	prev;

	if (base > 1)
	{
		if (n == 0)
			return (1);
		i = n;
		cnt = 0;
		while (i >= 1)
		{
			prev = i;
			i = i / base;
			if (prev == 1 && prev == i)
				return (cnt + 1);
			cnt++;
		}
		return (cnt);
	}
	return (0);
}

char	*ft_luitoa_base(long unsigned int n, int base, char *base_str)
{
	int		n_len;
	char	*ptr_n;
	int		cnt;

	if (base <= 1 || base_str == NULL)
		return (NULL);
	if ((int)ft_strlen((const char *)base_str) != base)
		return (NULL);
	n_len = ft_nblen(n, base);
	ptr_n = ft_calloc(n_len + 1, 1);
	if (ptr_n == NULL)
		return (NULL);
	cnt = n_len - 1;
	if (n == 0)
		ptr_n[0] = '0';
	else
	{
		while (n >= 1 && cnt >= 0)
		{
			ptr_n[cnt] = base_str[n % base];
			n = n / base;
			cnt--;
		}
	}
	return (ptr_n);
}
