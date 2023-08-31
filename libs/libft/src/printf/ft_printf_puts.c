/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_puts.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 11:28:03 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/04 09:47:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	pf_putdi(va_list ptr_var)
{
	return (pf_putint(va_arg(ptr_var, int), 10, BASE10));
}

int	pf_putu(va_list ptr_var)
{
	return (pf_putluint(va_arg(ptr_var, unsigned int), 10, BASE10));
}

int	pf_putx(va_list ptr_var)
{
	return (pf_putluint(va_arg(ptr_var, unsigned int), 16, BASE16_L));
}

int	pf_put_capx(va_list ptr_var)
{
	return (pf_putluint(va_arg(ptr_var, unsigned int), 16, BASE16_U));
}

int	pf_put_lui(va_list ptr_var)
{
	return (pf_putluint(va_arg(ptr_var, long unsigned int), 10, BASE10));
}
