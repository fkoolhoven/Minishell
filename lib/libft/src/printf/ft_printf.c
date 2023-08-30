/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 10:05:41 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/04 09:47:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "ft_printf.h"

int	pf_putvar(int fnd_del, const char *str, va_list ptr_var, int *ptr_wrt)
{
	int	fnd_spec;
	int	wrt;

	fnd_spec = pf_strchr_i(SPECS, str[fnd_del + 1]);
	if (SPECS[fnd_spec] != '\0')
	{
		wrt = pf_select_function(fnd_spec, ptr_var);
		*ptr_wrt = wrt;
		return (fnd_del + 2);
	}
	if (str[fnd_del + 1] != '\0')
	{
		wrt = write(1, str + fnd_del + 1, 1);
		*ptr_wrt = wrt;
		return (fnd_del + 2);
	}
	return (fnd_del + 1);
}

static int	st_helper(const char *str, va_list ptr_var)
{
	int	fnd_del;
	int	wrt;
	int	rtn;

	rtn = 0;
	while (*str)
	{
		fnd_del = pf_strchr_i(str, '%');
		wrt = write(1, str, fnd_del);
		if (wrt == -1)
			return (-1);
		rtn += wrt;
		if (str[fnd_del] != '\0')
		{
			str += pf_putvar(fnd_del, str, ptr_var, &wrt);
			if (wrt == -1)
				return (-1);
			rtn += wrt;
		}
		else
			str += fnd_del;
	}
	return (rtn);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr_var;

	if (str == NULL)
		return (0);
	va_start(ptr_var, str);
	return (st_helper(str, ptr_var));
}
