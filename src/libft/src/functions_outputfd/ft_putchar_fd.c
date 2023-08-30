/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:58:28 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:05:25 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_putchar_fd().
 * ft_putchar_fd(char c, int fd):
		This function uses write() to put the character c in 
		the file, stdout, stdin or stderr.
		If the fd is negative or is bigger than 
		the maximal file descriptor possible, 
		the function does not do anything.
		This function has no return value.
 */

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0 || fd < FD_SETSIZE)
		write(fd, &c, 1);
}
