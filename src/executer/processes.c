/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   processes.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 12:02:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 15:18:01 by jhendrik      ########   odam.nl         */
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

int	parent_one_command(t_exec_var *var, t_process *ch_proclst)
{
	int	waitstatus;

	wrap_sighandler(SIGINT, SIG_IGN);
	close_pipes(var);
	if (ch_proclst != NULL)
		waitstatus = wait_for_all(var->process_lst);
	else
		waitpid(var->process, &waitstatus, 0);
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	if (waitstatus == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (WIFEXITED(waitstatus))
		return (WEXITSTATUS(waitstatus));
	else if (WIFSIGNALED(waitstatus))
		return (128 + WTERMSIG(waitstatus));
	else
		return (EXIT_SUCCESS);
}

int	parent_process(t_exec_var *var, int j)
{
	t_process	*check;

	if (j < var->last_cmnd - 1)
	{
		close_given_pipe(var->prev_pipe);
		check = process_make_add_node(&(var->process_lst), var->process);
		var->prev_pipe[0] = var->fd_pipe[0];
		var->prev_pipe[1] = var->fd_pipe[1];
		if (check == NULL)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (j == var->last_cmnd - 1)
	{
		check = process_make_add_node(&(var->process_lst), var->process);
		if (check == NULL)
		{
			ft_putstr_fd("Warning: making pid list failed\n", STDERR_FILENO);
			ft_putstr_fd("\t waiting for last process\n", STDERR_FILENO);
		}
		return (parent_one_command(var, check));
	}
	terminate_execvar_parent(&var);
	return (EXIT_SUCCESS);
}
