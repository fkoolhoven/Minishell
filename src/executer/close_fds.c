/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   close_fds.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 15:37:26 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/25 15:39:23 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_close_fdarray(int *fds, size_t size)
{
	size_t	i;

	if (fds != NULL)
	{
		i = 0;
		while (i < size)
		{
			if (fds[i] >= 3)
			{
				close(fds[i]);
				fds[i] = -1;
			}
			i++;
		}
	}
}

void	close_given_pipe(int *fds)
{
	if (fds != NULL)
		st_close_fdarray(fds, 2);
}

void	close_read_end(int *fds)
{
	if (fds != NULL)
	{
		if (fds[0] >= 3)
		{
			close(fds[0]);
			fds[0] = -1;
		}
	}
}

void	close_write_end(int *fds)
{
	if (fds != NULL)
	{
		if (fds[1] >= 3)
		{
			close(fds[1]);
			fds[1] = -1;
		}
	}
}

void	close_pipes(t_exec_var *var)
{
	if (var != NULL)
	{
		if (var->fd_pipe != NULL)
			st_close_fdarray(var->fd_pipe, 2);
		if (var->prev_pipe != NULL)
			st_close_fdarray(var->prev_pipe, 2);
	}
}
