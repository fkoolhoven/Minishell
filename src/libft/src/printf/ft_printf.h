/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 12:27:07 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/04 09:47:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>

# define BASE10 "0123456789"
# define BASE16_L "0123456789abcdef"
# define BASE16_U "0123456789ABCDEF"
# define SPECS "cspdiuxXL"

typedef int	(*t_pf_function)(va_list);
int	pf_strchr_i(const char *str, char c);
int	pf_putchar_wrt(va_list ptr_var);
int	pf_putstr_wrt(va_list ptr_var);
int	pf_putptr(va_list ptr_var);
int	pf_putdi(va_list ptr_var);
int	pf_putu(va_list ptr_var);
int	pf_putx(va_list ptr_var);
int	pf_put_capx(va_list ptr_var);
int	pf_put_lui(va_list ptr_var);
int	pf_putint(int n, int base, char *str_base);
int	pf_putluint(long unsigned int n, int base, char *str_base);
int	ft_printf(const char *str, ...);
int	pf_select_function(int i, va_list ptr_var);

#endif
