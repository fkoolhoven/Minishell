/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   errors.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 17:36:15 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/09 17:23:06 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	exec_error_swap(int fd_in, int fd_out, t_exec_var *var)
{
	if (fd_in >= 3)
		close(fd_in);
	if (fd_out >= 3)
		close(fd_out);
	if (var != NULL)
	{
		if (var->fd_pipe != NULL)
		{
			if (var->fd_pipe[0] >= 3)
				close(var->fd_pipe[0]);
			if (var->fd_pipe[1] >= 3)
				close(var->fd_pipe[1]);
		}
		if (var->fd_read >= 3)
			close(var->fd_read);
	}
	return (EXIT_FAILURE);
}

int	exec_error_child_denied(t_exec_var *var, char *val_cmnd, t_command *cmnd)
{
	if (cmnd != NULL)
	{
		if (cmnd->command != NULL)
		{
			if ((cmnd->command)[0] != NULL)
				ft_putstr_fd((cmnd->command)[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
	if (var != NULL)
	{
		terminate_command_list(&(var->cmnd_list));
		terminate_hashtable(var->env);
		ft_free_str_array(var->env_str);
	}
	if (val_cmnd != NULL)
		free(val_cmnd);
	return (126);
}

int	exec_error_child_notfound(t_exec_var *var, char *val_cmnd, t_command *cmnd)
{
	if (cmnd != NULL)
	{
		if (cmnd->command != NULL)
		{
			if ((cmnd->command)[0] != NULL)
				ft_putstr_fd((cmnd->command)[0], 2);
			ft_putstr_fd(": Command not found\n", 2);
		}
	}
	if (var != NULL)
	{
		terminate_command_list(&(var->cmnd_list));
		terminate_hashtable(var->env);
		ft_free_str_array(var->env_str);
	}
	if (val_cmnd != NULL)
		free(val_cmnd);
	return (127);
}

int	exec_error_parent(t_exec_var *var)
{
	if (var != NULL)
	{
		if (var->env_str != NULL)
			ft_free_str_array(var->env_str);
		if (var->fd_pipe != NULL)
		{
			if ((var->fd_pipe)[0] >= 3)
				close((var->fd_pipe)[0]);
			if ((var->fd_pipe)[1] >= 3)
				close((var->fd_pipe)[1]);
		}
		if (var->fd_read >= 3)
			close(var->fd_read);
	}
	return (EXIT_FAILURE);
}

int	exec_error_parent_nopipe(t_exec_var *var)
{
	if (var != NULL)
	{
		if (var->env_str != NULL)
			ft_free_str_array(var->env_str);
		if (var->fd_read >= 3)
			close(var->fd_read);
	}
	return (EXIT_FAILURE);
}
