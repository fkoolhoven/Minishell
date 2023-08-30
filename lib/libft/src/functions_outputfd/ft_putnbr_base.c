/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 12:47:06 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:05:58 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions rec_putint() and ft_putnbr_fd_base().
 * rec_putint(int n, int base, char *sbase, int *ptr, int fd):
		This function outputs the number n (given in base ten) 
		in the given base to the file descriptor fd recursively.
		If n is a digit in base base, the function outputs 
		the corresponding digit in sbase to the file descriptor fd.
		If n is negative, the function outputs a minus and
		calls itself with -n.
		If n is INT_MIN, this goes wrong since -INT_MIN is bigger than INT_MAX.
		This case is hard coded.
		Otherwise, the function calls itself first with n/base 
		and then with n%base (n modulo base).
		This function has no return value.
 * ft_putnbr_fd_base(int n, int base, char *sbase, int fd):
		This function outputs the number n (given in base ten)
		in the given base to the file descriptor fd if fd is a 
		valid file descriptor and base is a valid base, and sbase has length base.
		This function has no return value.
 */

static void	rec_putint(int n, int base, char *sbase, int fd)
{
	if (n >= 0 && n <= (base - 1))
		write(fd, sbase + n, 1);
	else if (n == -2147483648)
	{
		rec_putint(n / base, base, sbase, fd);
		rec_putint((-1) * (n % base), base, sbase, fd);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		rec_putint((-1) * n, base, sbase, fd);
	}
	else
	{
		rec_putint(n / base, base, sbase, fd);
		rec_putint(n % base, base, sbase, fd);
	}
}

void	ft_putnbr_fd_base(int n, int base, char *sbase, int fd)
{
	if (fd >= 0 || fd < FD_SETSIZE)
	{
		if (base > 1 && (size_t)base == ft_strlen(sbase))
			rec_putint(n, base, sbase, fd);
	}
}
