/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 12:24:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/04 09:47:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	st_strlen_n(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	pf_strchr_i(const char *str, char c)
{
	int	j;

	if (str == NULL)
		return (-1);
	j = 0;
	while (str[j] && str[j] != c)
		j++;
	return (j);
}

int	pf_putchar_wrt(va_list ptr_var)
{
	char	numchar;

	numchar = va_arg(ptr_var, int);
	return (write(1, &numchar, 1));
}

int	pf_putstr_wrt(va_list ptr_var)
{
	char	*str;

	str = va_arg(ptr_var, char *);
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, st_strlen_n(str)));
}

int	pf_putptr(va_list ptr_var)
{
	void				*ptr;
	int					wrt;
	int					rtn;
	long unsigned int	lui_ptr;

	ptr = va_arg(ptr_var, void *);
	if (ptr == NULL)
		return (write(1, "0x0", 3));
	wrt = write(1, "0x", 2);
	if (wrt == -1)
		return (-1);
	rtn = wrt;
	lui_ptr = (long unsigned int)ptr;
	wrt = pf_putluint(lui_ptr, 16, BASE16_L);
	if (wrt == -1)
		return (-1);
	rtn += wrt;
	return (rtn);
}
