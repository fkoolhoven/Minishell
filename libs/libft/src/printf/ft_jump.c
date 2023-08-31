/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_jump.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 15:38:06 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/04 09:47:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	pf_select_function(int i, va_list ptr_var)
{
	t_pf_function	jmptbl[9];

	jmptbl[0] = &pf_putchar_wrt;
	jmptbl[1] = &pf_putstr_wrt;
	jmptbl[2] = &pf_putptr;
	jmptbl[3] = &pf_putdi;
	jmptbl[4] = &pf_putdi;
	jmptbl[5] = &pf_putu;
	jmptbl[6] = &pf_putx;
	jmptbl[7] = &pf_put_capx;
	jmptbl[8] = &pf_put_lui;
	return (jmptbl[i](ptr_var));
}
