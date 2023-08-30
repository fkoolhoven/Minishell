/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 15:32:59 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:05:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_putendl_fd().
 * ft_putendl_fd(char *s, int fd):
		This function outputs the string s to the 
		file descriptor fd by calling ft_putstr_fd and 
		after this outputs an enter ('\n') to the 
		file descriptor fd by calling ft_putchar_fd() if 
		fd is a valid file descriptor.
		This function has no return value.
 */

void	ft_putendl_fd(char *s, int fd)
{
	if (fd >= 0 || fd < FD_SETSIZE)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
