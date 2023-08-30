/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 15:48:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:06:10 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions rec_putnbr_fd() and ft_putnbr_fd().
 * rec_putnbr_fd(int n, int fd):
		This function recursively outputs the number n 
		(in base ten) to the file descriptor fd.
		If the number n is a digit, the function 
		can output the number n to the file descriptor fd.
		If the number n is negative, the function outputs 
		a minus and calls itself with -n. 
		Because -INT_MIN is bigger than INT_MAX, this case is hard coded.
		Otherwise, the function calls itself first with n/10 and then with n%10.
		This function has no output value.
 * ft_putnbr_fd(int n, int fd):
		This function outputs the number n (in base ten)
		to the file descriptor fd, if fd is a valid file descriptor.
		This function has no output value.
 */

void	rec_putnbr_fd(int n, int fd)
{
	char	numchar;

	if (n >= 0 && n <= 9)
	{
		numchar = n + '0';
		write(fd, &numchar, 1);
	}
	else if (n == -2147483648)
	{
		numchar = 2 + '0';
		write(fd, "-", 1);
		write(fd, &numchar, 1);
		rec_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		rec_putnbr_fd((-1) * n, fd);
	}
	else
	{
		rec_putnbr_fd(n / 10, fd);
		rec_putnbr_fd(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd >= 0 || fd < FD_SETSIZE)
		rec_putnbr_fd(n, fd);
}
