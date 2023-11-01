/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_one_cmnd.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 12:29:25 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/30 16:52:55 by jhendrik      ########   odam.nl         */
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
	terminate_execvar_parent(&var);
	if (check == EXIT_SUCCESS || status != EXIT_SUCCESS)
		return (status);
	return (check);
}

static int	st_exec_onecmnd_process(t_exec_var *var)
{
	int			exit_status;
	t_process	*check;

	var->process = fork();
	if (var->process < 0)
		return (exec_error_parent(var));
	else
	{
		if (var->process == 0)
			return (child_process_onecmnd(var, var->cmnd_list));
		else
		{
			check = process_make_add_node(&(var->process_lst), var->process);
			exit_status = parent_one_command(var, check);
			return (terminate_execvar_parent(&var), exit_status);
		}
	}
}

int	execute_one_cmnd(t_exec_var *var)
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
		return (st_exec_onecmnd_process(var));
}
