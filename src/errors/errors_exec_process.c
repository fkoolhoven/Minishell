/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec_process.c                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:24:45 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/23 12:38:26 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		terminate_execvar_child(&var);
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
		terminate_execvar_child(&var);
	if (val_cmnd != NULL)
		free(val_cmnd);
	return (127);
}

int	exec_error_parent(t_exec_var *var)
{
	terminate_execvar_parent(&var);
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
		if (var->cmnd_list != NULL)
		{
			heredoc_unlinker(var->cmnd_list);
			terminate_command_list(&(var->cmnd_list));
		}
	}
	return (EXIT_FAILURE);
}
