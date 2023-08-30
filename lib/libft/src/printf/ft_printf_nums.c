/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_nums.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 12:25:06 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/04 09:47:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

static void	check_wrt(int wrt, int *ptr)
{
	if (wrt == -1 || *ptr == -1)
		*ptr = -1;
	else
		(*ptr) += 1;
}

static void	rec_putint(int n, int base, char *str_base, int *ptr)
{
	int	wrt;

	wrt = 0;
	if (n >= 0 && n <= (base - 1))
	{
		wrt = write(1, str_base + n, 1);
		check_wrt(wrt, ptr);
	}
	else if (n == -2147483648)
	{
		rec_putint(n / base, base, str_base, ptr);
		rec_putint((-1) *(n % base), base, str_base, ptr);
	}
	else if (n < 0)
	{
		wrt = write(1, "-", 1);
		check_wrt(wrt, ptr);
		rec_putint((-1) * n, base, str_base, ptr);
	}
	else
	{
		rec_putint(n / base, base, str_base, ptr);
		rec_putint(n % base, base, str_base, ptr);
	}
}

int	pf_putint(int n, int base, char *str_base)
{
	int	cnt;
	int	*ptr;

	if (base > 1)
	{
		cnt = 0;
		ptr = &cnt;
		rec_putint(n, base, str_base, ptr);
		return (cnt);
	}
	return (0);
}

static void	rec_putluint(long unsigned int n, int base, char *sb, int *ptr)
{
	int	wrt;

	wrt = 0;
	if (n >= 0 && n <= (long unsigned int)(base - 1))
	{
		wrt = write(1, sb + n, 1);
		if (wrt == -1 || *ptr == -1)
			*ptr = -1;
		else
			(*ptr) += 1;
	}
	else
	{
		rec_putluint(n / base, base, sb, ptr);
		rec_putluint(n % base, base, sb, ptr);
	}
}

int	pf_putluint(long unsigned int n, int base, char *str_base)
{
	int	cnt;
	int	*ptr;

	if (base > 1)
	{
		cnt = 0;
		ptr = &cnt;
		rec_putluint(n, base, str_base, ptr);
		return (cnt);
	}
	return (0);
}
