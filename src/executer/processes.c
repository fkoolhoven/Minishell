/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   processes.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 12:02:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/09 17:28:58 by jhendrik      ########   odam.nl         */
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
	exit(EXIT_FAILURE);
}

/* Parentprocess
   		To do:		1.	Write exec_error_handler function
					2.	...
		Explanation:	This function checks whether we are at the last parent process
						or if we need to go on to produce more child processes
						If it is the last parent process, then j == last_cmnd
							and this process needs to wait for the last childprocess to 
							end and return the proper exit status
							... also, the heredocs are unlinked here, maybe it should be
							done somewhere else, unless the executer also produces the
							heredoc files.
						If it is not the last parent process, then j != last_cmnd,
							and it sets STDIN to the known pipes read-end so the pipe
							can be reused for the next childprocess
   */
/*int	parent_process(t_exec_var *var, int j)
{
	int	waitstatus;

	if (j < var->last_cmnd - 1)
	{
		if (dup2(var->fd_pipe[0], STDIN_FILENO) < 0)
			return (exec_error_parent(var));
		close(var->fd_pipe[0]);
		close(var->fd_pipe[1]);
		return (EXIT_SUCCESS);
	}
	else if (j == var->last_cmnd - 1)
	{
		ft_putstr_fd("Got to last parent\n", 2);
		wrap_sighandler(SIGINT, SIG_IGN);
		waitpid(var->process, &waitstatus, 0);
		waitpid(0, NULL, 0);
		wrap_sighandler(SIGINT, &catch_sigint_parent);
		ft_putstr_fd("About to return status\n", 2);
		if (WIFEXITED(waitstatus))
			return (WEXITSTATUS(waitstatus));
		else if (WIFSIGNALED(waitstatus))
			return (128 + WTERMSIG(waitstatus));
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
} */

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
