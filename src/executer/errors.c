/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   errors.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 17:36:15 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/04 18:30:49 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	exec_error_swap(int fd_in, int fd_out, int *fd_pipe)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
	if (fd_pipe != NULL)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	return (EXIT_FAILURE);
}

int	exec_error_child(t_exec_var *var, char *val_cmnd, int errno, char *errmess)
{
	if (var != NULL)
	{
		terminate_command_list(&(var->cmnd_list));
		terminate_hashtable(var->env);
		ft_free_str_array(var->env_str);
	}
	if (val_cmnd != NULL)
		free(val_cmnd);
	if (!(errmess))
		perror(errmess);
	else
	{
		ft_putstr_fd(val_cmnd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(errmess, 2);
	}
	if (val_cmnd != NULL)
		free(val_cmnd);
	return (errno);
}

int	exec_error_parent(t_exec_var *var)
{
	if (var != NULL)
	{
		if (var->env_str != NULL)
			ft_free_str_array(var->env_str);
		if (var->fd_pipe != NULL)
		{
			if ((var->fd_pipe)[0] >= 0)
				close((var->fd_pipe)[0]);
			if ((var->fd_pipe)[1] >= 0)
				close((var->fd_pipe)[1]);
		}
	}
	return (EXIT_FAILURE);
}
