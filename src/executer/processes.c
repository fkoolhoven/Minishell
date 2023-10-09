/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   processes.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 12:02:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/09 17:39:27 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	child_process_onecmnd(t_exec_var *var, t_command *cmnd)
{
	int		bltin_index;
	int		check;
	char	*valid_cmnd;

	if (var != NULL && cmnd != NULL)
	{
		check = swap_filedescriptors(var, cmnd);
		if (check == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		bltin_index = check_if_builtin(var, cmnd);
		wrap_sighandler(SIGINT, SIG_DFL);
		if (bltin_index >= 0)
			exit(execute_builtin(var, cmnd, bltin_index));
		else
		{
			valid_cmnd = find_command_path(var, cmnd);
			execve(valid_cmnd, cmnd->command, var->env_str);
			if (valid_cmnd == NULL)
				exit(exec_error_child_notfound(var, valid_cmnd, cmnd));
			exit(exec_error_child_denied(var, valid_cmnd, cmnd));
		}
	}
	terminate_execvar(var);
	exit(EXIT_FAILURE);
}

int	child_process(t_exec_var *var, t_command *cmnd)
{
	int		bltin_index;
	int		check;
	char	*valid_cmnd;

	if (var != NULL && cmnd != NULL)
	{
		wrap_sighandler(SIGINT, SIG_DFL);
		check = swap_filedescriptors(var, cmnd);
		if (check == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		bltin_index = check_if_builtin(var, cmnd);
		if (bltin_index >= 0)
			exit(execute_builtin(var, cmnd, bltin_index));
		else
		{
			valid_cmnd = find_command_path(var, cmnd);
			execve(valid_cmnd, cmnd->command, var->env_str);
			if (valid_cmnd == NULL)
				exit(exec_error_child_notfound(var, valid_cmnd, cmnd));
			exit(exec_error_child_denied(var, valid_cmnd, cmnd));
		}
	}
	terminate_execvar(var);
	exit(EXIT_FAILURE);
}

int	parent_process(t_exec_var *var, int j)
{
	int	waitstatus;

	if (j < var->last_cmnd - 1)
	{
		if (var->fd_read >= 3)
			close(var->fd_read);
		var->fd_read = var->fd_pipe[0];
		close(var->fd_pipe[1]);
		return (EXIT_SUCCESS);
	}
	else if (j == var->last_cmnd - 1)
	{
		wrap_sighandler(SIGINT, SIG_IGN);
		waitpid(var->process, &waitstatus, 0);
		waitpid(-1, NULL, 0);
		wrap_sighandler(SIGINT, &catch_sigint_parent);
		terminate_execvar(var);
		if (WIFEXITED(waitstatus))
			return (WEXITSTATUS(waitstatus));
		else if (WIFSIGNALED(waitstatus))
			return (128 + WTERMSIG(waitstatus));
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	parent_one_command(t_exec_var *var)
{
	int	waitstatus;

	wrap_sighandler(SIGINT, SIG_IGN);
	waitpid(var->process, &waitstatus, 0);
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	terminate_execvar(var);
	if (WIFEXITED(waitstatus))
		return (WEXITSTATUS(waitstatus));
	else if (WIFSIGNALED(waitstatus))
		return (128 + WTERMSIG(waitstatus));
	else
		return (EXIT_SUCCESS);
}
