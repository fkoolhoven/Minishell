/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:24:45 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/20 12:39:55 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error_swap(int fd_in, int fd_out, t_exec_var *var)
{
	if (fd_in >= 3)
		close(fd_in);
	if (fd_out >= 3)
		close(fd_out);
	terminate_execvar(var);
	perror(NULL);
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
		terminate_execvar(var);
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
		terminate_execvar(var);
	}
	if (val_cmnd != NULL)
		free(val_cmnd);
	return (127);
}

int	exec_error_parent(t_exec_var *var)
{
	terminate_execvar(var);
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
