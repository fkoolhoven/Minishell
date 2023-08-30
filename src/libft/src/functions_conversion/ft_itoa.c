/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:50:04 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:09:24 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions:
			- ft_while_nblen()
			- ft_nblen()
			- fill_str_negwhile()
			- fill_str()
			- ft_itoa()
 * ft_while_nblen(unsigned int n):
 		This function is a helper function for ft_nblen().
		This function returns the amount of digits the input consists of
	   	if it would be displayed in base ten.
		This function can only take positive integers as input.
 * ft_nblen(int n):
 		This function returns the amount of characters the number consists of, 
		if it is displayed in base ten.
 * fill_str_negwhile(int n, int n_len, char *ptr_n):
 		This function is a helper function for fill_str().
		This function fills the string pointed to by ptr_n 
		with the appropriate characters based on n.
		This function can only take negative integers for n.
 * fill_str(int n, int n_len, char *ptr_n):
 		This function fills the string pointed to by ptr_n
		with the appropriate characters based on n and n_len.
 * ft_itoa(int n):
		This function converts the integer n to a string.
		The memory needed is allocated using malloc.
		If the malloc fails, the function returns a NULL-pointer.
		Otherwise, the function returns a pointer to the string.
 */

static int	ft_while_nblen(unsigned int n)
{
	unsigned int	i;
	int				cnt;

	i = 1;
	cnt = 0;
	while (n / i >= 1 && cnt < 10)
	{
		cnt++;
		i = i * 10;
	}
	return (cnt);
}

static int	ft_nblen(int n)
{
	int	abs_n;

	if (n > 0)
		return (ft_while_nblen(n));
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	abs_n = (-1) * n;
	return (ft_while_nblen(abs_n) + 1);
}

static void	fill_str_negwhile(int n, int n_len, char *ptr_n)
{
	int	cnt;
	int	abs_n;

	cnt = n_len - 1;
	ptr_n[0] = '-';
	if (n == -2147483648)
	{
		ptr_n[cnt] = '8';
		abs_n = 214748364;
		cnt--;
	}
	else
		abs_n = (-1) * n;
	while (abs_n >= 1 && cnt >= 1)
	{
		ptr_n[cnt] = abs_n % 10 + '0';
		abs_n = abs_n / 10;
		cnt--;
	}
}

static void	fill_str(int n, int n_len, char *ptr_n)
{
	int	cnt;
	int	abs_n;

	cnt = n_len - 1;
	ptr_n[n_len] = '\0';
	if (n < 0)
		fill_str_negwhile(n, n_len, ptr_n);
	else
	{
		abs_n = n;
		if (abs_n == 0)
			ptr_n[0] = '0';
		else
		{
			while (abs_n >= 1 && cnt >= 0)
			{
				ptr_n[cnt] = abs_n % 10 + '0';
				abs_n = abs_n / 10;
				cnt--;
			}
		}
	}
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	*ptr_n;

	n_len = ft_nblen(n);
	ptr_n = (char *)malloc(n_len + 1);
	if (ptr_n == NULL)
		return (NULL);
	fill_str(n, n_len, ptr_n);
	return (ptr_n);
}
