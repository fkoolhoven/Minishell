/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 12:06:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:09:35 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions
			- ft_nblen_abs()
			- ft_nblen()
			- fill_str_neg()
			- fill_str_pos()
			- ft_itoa_base()
 *ft_nblen_abs(int n, int base):
 		This function is a helper function for ft_nblen().
		This function returns the amount of digits if n would be displayed in base.
		This function only works if input for n is positive.
		This function will not work properly if 
		n displayed in base has more than INT_MAX digits.

 *ft_nblen(int n, int base):
 		This function returns the amount of digits if n would be displayed in base.
		For this it calls ft_nblen_abs() with the appropriate input. 
		This function will not work properly if 
		n displayed in base has more than INT_MAX digits.

 *fill_str_neg(int n, int n_len, int base, char *base_str):
 		This function allocates (with malloc) and fills a string 
		with n displayed in base.
		If malloc fails, the function returns NULL.
		This function only works properly if input for n is negative 
		and base_str has length base.
		This function returns a pointer to the new string.

 *fill_str_pos(int n, int n_len, int base, char *base_str):
 		This function allocates (with malloc) and fills a string
		with n displayed in base.
		If malloc fails the function returns NULL.
		This function only works properly if input for n is positive
		and base_str has length base.
		This function has returns a pointer to the new string.

 *ft_itoa_base(int n, int base, char *base_str):
 		This function converts the integer n to a string.
		In the string the n will be displayed in the given base 
		as given in the base string pointed to by base_str.
		The memory for the string is allocated with malloc by calling ft_calloc().
		If malloc fails, the function returns a NULL-pointer.
		If the string pointed to by base_str does not have length equal 
		to the given integer base, the function returns a NULL-pointer.
		If an invalid base or base_str is a NULL-pointer, 
		the function returns a NULL-pointer.
		This function only accepts the integer n in base ten representation,
		in any other base the function returns the wrong value.
 */

static int	ft_nblen_abs(int n, int base)
{
	int	i;
	int	prev;
	int	cnt;

	if (base > 1 && n >= 0)
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

static int	ft_nblen(int n, int base)
{
	if (n >= 0 && base > 1)
		return (ft_nblen_abs(n, base));
	else if (n == -2147483648 && base > 1)
		return (ft_nblen_abs((-1) * (n / base), base) + 2);
	else if (n < 0 && base > 1)
		return (ft_nblen_abs((-1) * n, base) + 1);
	else
		return (-1);
}

static char	*fill_str_neg(int n, int n_len, int base, char *base_str)
{
	int		cnt;
	char	*ptr_n;

	ptr_n = ft_calloc(n_len + 1, sizeof(char));
	if (ptr_n == NULL)
		return (NULL);
	cnt = n_len - 1;
	ptr_n[n_len] = '\0';
	ptr_n[0] = '-';
	if (n == -2147483648)
	{
		ptr_n[cnt] = base_str[(-1) * (n % base)];
		n = (-1) * (n / base);
		cnt--;
	}
	else
		n = (-1) * n;
	while (n >= 1 && cnt >= 1)
	{
		ptr_n[cnt] = base_str[n % base];
		n = n / base;
		cnt--;
	}
	return (ptr_n);
}

static char	*fill_str_pos(int n, int n_len, int base, char *base_str)
{
	int		cnt;
	char	*ptr_n;

	ptr_n = ft_calloc(n_len + 1, sizeof(char));
	if (ptr_n == NULL)
		return (NULL);
	cnt = n_len - 1;
	ptr_n[n_len] = '\0';
	if (n > 0 && base > 1)
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

char	*ft_itoa_base(int n, int base, char *base_str)
{
	int		n_len;
	char	*ptr_n;

	if (base <= 1 || base_str == NULL)
		return (NULL);
	if (ft_strlen((const char *)base_str) != (size_t)base)
		return (NULL);
	n_len = ft_nblen(n, base);
	if (n == 0)
	{
		ptr_n = ft_calloc(n_len + 1, sizeof(char));
		if (ptr_n == NULL)
			return (NULL);
		ptr_n[0] = '0';
		ptr_n[1] = '\0';
		return (ptr_n);
	}
	if (n > 0)
		return (fill_str_pos(n, n_len, base, base_str));
	else
		return (fill_str_neg(n, n_len, base, base_str));
}
