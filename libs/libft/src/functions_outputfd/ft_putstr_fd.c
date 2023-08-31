/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 15:23:56 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:06:20 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_putstr_fd().
 * ft_putstr_fd(char *s, int fd):
		This function outputs the string pointed to by s to 
		the given file descriptor if fd is a valid file descriptor.
		This function has no return value.
 */

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (fd >= 0 || fd < FD_SETSIZE)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}
