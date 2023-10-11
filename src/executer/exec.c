/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/11 16:30:23 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	st_execute_one_cmnd(t_exec_var *var)
{
	int	bltin_index;

	if (var == NULL)
		return (EXIT_FAILURE);
	if (var->cmnd_list == NULL)
		return (EXIT_FAILURE);
	bltin_index = check_if_builtin(var, var->cmnd_list);
	if (bltin_index >= 0)
		return (execute_builtin(var, var->cmnd_list, bltin_index));
	else
	{
		var->process = fork();
		if (var->process < 0)
			return (exec_error_parent(var));
		else
		{
			if (var->process == 0)
				return (child_process_onecmnd(var, var->cmnd_list));
			else
				return (parent_one_command(var));
		}
	}
}

static int	st_execute_line(t_exec_var *var)
{
	t_command	*tmp;
	int			j;
	int			status;

	if (var != NULL)
	{
		j = 0;
		tmp = var->cmnd_list;
		while (j < var->last_cmnd)
		{
			if (j < var->last_cmnd - 1 && pipe(var->fd_pipe) < 0)
				return (exec_error_parent_nopipe(var));
			var->process = fork();
			if (var->process < 0)
				return (exec_error_parent(var));
			else if (var->process != 0)
				status = parent_process(var, j);
			else
				child_process(var, tmp);
			j++;
			tmp = tmp->next;
		}
		return (status);
	}
	return (EXIT_FAILURE);
}

int	execute(t_command *cmnd_list, t_htable *environ, int exit_status)
{
	t_exec_var	var;
	int			fd[2];

	if (cmnd_list == NULL || environ == NULL)
		return (EXIT_FAILURE);
	var.cmnd_list = cmnd_list;
	var.env = environ;
	var.env_str = convert_htable_to_strarray(environ);
	if (var.env_str == NULL)
		return (EXIT_FAILURE);
	fd[0] = -1;
	fd[1] = -1;
	var.fd_pipe = fd;
	var.process = 1;
	var.exit_status = exit_status;
	var.fd_read = -1;
	var.last_cmnd = size_cmndlist(cmnd_list);
	create_all_outfiles(&var);
	if (var.last_cmnd == 1)
		return (st_execute_one_cmnd(&var));
	else
		return (st_execute_line(&var));
}
