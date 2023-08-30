/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putlui_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 13:46:41 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:05:47 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions rec_putluint() and ft_putlui_fd_base().
 * rec_putluint(long unsigned int n, int base, char *sb, int *ptr, int fd):
		This function outputs the number n (given in base ten) 
		to the file descriptor fd in base base.
		If n is a digit considered in base base, 
		the function outputs the corresponding character in base string (sb) 
		to the file descriptor fd.
		Otherwise, the function calls itself first 
		with n/base and then with n%base (n modulo base).
		This function has no output.
 * ft_putlui_fd_base(long unsigned int n, int base, char *sb, int fd):
		This function outputs the number n (given in base ten)
		to the file descriptor fd in base base if fd is a valid
		file descriptor and base is a valid base and length of base
		string (sb) is base.
		It does this by calling rec_putluint().
		Otherwise, this function does not do anything.
		This function has no output.
 */

static void	rec_putluint(long unsigned int n, int base, char *sb, int fd)
{
	if (n >= 0 && n <= (long unsigned int)(base - 1))
		write(fd, sb + n, 1);
	else
	{
		rec_putluint(n / base, base, sb, fd);
		rec_putluint(n % base, base, sb, fd);
	}
}

void	ft_putlui_fd_base(long unsigned int n, int base, char *sb, int fd)
{
	if (fd >= 0 && fd < FD_SETSIZE)
	{
		if (base > 1 && (size_t)base == ft_strlen(sb))
			rec_putluint(n, base, sb, fd);
	}
}
