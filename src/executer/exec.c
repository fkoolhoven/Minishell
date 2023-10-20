/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/20 11:23:51 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	st_execute_onecmnd_bltin(t_exec_var *var, int bltin_index)
{
	int	check;
	int	status;
	int	fd_stdin;
	int	fd_stdout;

	fd_stdout = -2;
	fd_stdin = -2;
	check = swap_mini(var, var->cmnd_list, &fd_stdin, &fd_stdout);
	if (check != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	status = execute_builtin(var, var->cmnd_list, bltin_index);
	check = swap_back_in_minishell(var, fd_stdin, fd_stdout);
	terminate_execvar(var);
	if (check == EXIT_SUCCESS || status != EXIT_SUCCESS)
		return (status);
	return (check);
}

static int	st_execute_one_cmnd(t_exec_var *var)
{
	int	bltin_index;

	if (var == NULL)
		return (EXIT_FAILURE);
	if (var->cmnd_list == NULL)
		return (EXIT_FAILURE);
	bltin_index = check_if_builtin(var, var->cmnd_list);
	if (bltin_index >= 0)
		return (st_execute_onecmnd_bltin(var, bltin_index));
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

int	execute(t_command *cmnd_list, t_htable *env, int estatus, char *cpath)
{
	t_exec_var	var;
	int			fd[2];

	if (cmnd_list == NULL || env == NULL)
		return (EXIT_FAILURE);
	var.cmnd_list = cmnd_list;
	var.env = env;
	var.cur_path = cpath;
	var.env_str = convert_htable_to_strarray(env);
	if (var.env_str == NULL)
		return (EXIT_FAILURE);
	fd[0] = -1;
	fd[1] = -1;
	var.fd_pipe = fd;
	var.process = 1;
	var.exit_status = estatus;
	var.fd_read = -1;
	var.last_cmnd = size_cmndlist(cmnd_list);
	create_all_outfiles(&var);
	if (var.last_cmnd == 1)
		return (st_execute_one_cmnd(&var));
	else
		return (st_execute_line(&var));
}
