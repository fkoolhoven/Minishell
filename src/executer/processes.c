/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   processes.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 12:02:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/23 17:04:21 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	child_process_onecmnd(t_exec_var *var, t_command *cmnd)
{
	int		check;
	char	*valid_cmnd;

	if (var != NULL && cmnd != NULL)
	{
		check = swap_filedescriptors(var, cmnd);
		if (check == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		wrap_sighandler(SIGINT, SIG_DFL);
		valid_cmnd = find_command_path(var, cmnd);
		execve(valid_cmnd, cmnd->command, var->env_str);
		if (valid_cmnd == NULL && !(heredoc_infile_found(cmnd->in)))
			exit(exec_error_child_notfound(var, valid_cmnd, cmnd));
		else if (valid_cmnd == NULL)
		{
			terminate_execvar_child(&var);
			exit(EXIT_SUCCESS);
		}
		exit(exec_error_child_denied(var, valid_cmnd, cmnd));
	}
	terminate_execvar_child(&var);
	exit(EXIT_FAILURE);
}

static int	st_child_command(t_exec_var *var, t_command *cmnd)
{
	char	*valid_cmnd;

	valid_cmnd = find_command_path(var, cmnd);
	execve(valid_cmnd, cmnd->command, var->env_str);
	if (valid_cmnd == NULL && !(heredoc_infile_found(cmnd->in)))
		exit(exec_error_child_notfound(var, valid_cmnd, cmnd));
	else if (valid_cmnd == NULL)
	{
		terminate_execvar_child(&var);
		exit(EXIT_SUCCESS);
	}
	exit(exec_error_child_denied(var, valid_cmnd, cmnd));
}

int	child_process(t_exec_var *var, t_command *cmnd)
{
	int		bltin_index;
	int		check;

	if (var != NULL && cmnd != NULL)
	{
		wrap_sighandler(SIGINT, SIG_DFL);
		check = swap_filedescriptors(var, cmnd);
		if (check == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		bltin_index = check_if_builtin(var, cmnd);
		if (bltin_index >= 0)
		{
			check = execute_builtin(var, cmnd, bltin_index);
			terminate_execvar_child(&var);
			exit(check);
		}
		else
			return (st_child_command(var, cmnd));
	}
	terminate_execvar_child(&var);
	exit(EXIT_FAILURE);
}

int	parent_one_command(t_exec_var *var)
{
	int	waitstatus;

	wrap_sighandler(SIGINT, SIG_IGN);
	waitpid(var->process, &waitstatus, 0);
	// this line fixes sleep 4 | ls, but breaks cat | cat | cat | ls (if it would work in the first place)
//	waitpid(-1, NULL, 0);
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	if (WIFEXITED(waitstatus))
		return (WEXITSTATUS(waitstatus));
	else if (WIFSIGNALED(waitstatus))
		return (128 + WTERMSIG(waitstatus));
	else
		return (EXIT_SUCCESS);
}

int	parent_of_grandchild(t_exec_var *var, t_command *cmnd)
{
	pid_t	process;
	int		waitstatus;

	if (var == NULL)
		exit(EXIT_FAILURE);
	if (cmnd == NULL)
	{
		terminate_execvar_child(&var);
		exit(EXIT_FAILURE);
	}
	process = fork();
	if (process < 0)
	{
		terminate_execvar_child(&var);
		exit(EXIT_FAILURE);
	}
	if (process == 0)
		waitstatus = child_process(var, cmnd);
	else 
	{
		wrap_sighandler(SIGINT, SIG_IGN);
		waitpid(process, &waitstatus, 0);
		wrap_sighandler(SIGINT, &catch_sigint_parent);
		terminate_execvar_child(&var);
		if (WIFEXITED(waitstatus))
			exit(WEXITSTATUS(waitstatus));
		else if (WIFSIGNALED(waitstatus))
			exit(128 + WTERMSIG(waitstatus));
		else
			exit(EXIT_SUCCESS);
	}
	exit(waitstatus);
}

int	grandparent_process(t_exec_var *var, int j)
{
	if (j < var->last_cmnd - 1)
	{
		if (var->fd_read >= 3)
			close(var->fd_read);
		var->fd_read = var->fd_pipe[0];
		close(var->fd_pipe[1]);
		return (EXIT_SUCCESS);
	}
	if (j == var->last_cmnd - 1)
		return (parent_one_command(var));
	return (EXIT_SUCCESS);
}
