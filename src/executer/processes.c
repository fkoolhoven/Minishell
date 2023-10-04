/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   processes.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 12:02:47 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/04 18:30:23 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* Childprocess: 
   		To add: 	1.	distinction between builtins and other commands --> DONE
					2.	get correct path for command ???
					3.	Write execute_builtin()
					4. 	Write exec_error_handler() or a special error_handler for this case 
					5. 	...
		Explanation:	The function first swaps the necessary filedescriptors by calling
							the function swap_filedescriptors(), this function closes all the 
							unnecessary filedescriptors 
						Then the function checks whether the command is a builtin by calling
							check_if_builtin() 
						If it is a builtin, the function execute_builtin() is called
						Otherwise, execve() is used
							This function only returns to the programming of original process
							if it cannot execute the command given
							which is either if the file has the wrong permissions (exit value is 126)
							or it doesn't exist (exit value is 127)

   */
void	child_process(t_exec_var *var, t_command *cmnd)
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
			execve(valid_cmnd, cmnd->command, var->env);
			if (valid_cmnd == NULL)
				exit(exec_error_child(var, valid_cmnd, 127, "Command not found\n"));
			exit(exec_error_child(var, valid_cmnd, 126, "Permission denied\n"));
		}
		wrap_sighandler(SIGINT, &catch_sigint_parent);
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
int	parent_process(t_exec_var *var, int j)
{
	int	waitstatus;

	if (j != var->last_cmnd)
	{
		if (dup2(var->fd_pipe[0], STDIN_FILENO) < 0)
			return (exec_error_parent(var));
		close(var->fd_pipe[0]);
		close(var->fd_pipe[1]);
		return (EXIT_SUCCESS);
	}
	else if (j == var->last_cmnd)
	{
		wrap_sighandler(SIGINT, SIG_IGN);
		waitpid(var->process, &waitstatus, 0);
		heredoc_unlinker(var->cmnd_list);
		wrap_sighandler(SIGINT, &catch_sigint_parent);
		if (WIFEXITED(waitstatus))
			return (WEXITSTATUS(waitstatus));
		else if (WIFSIGNALED(waitstatus))
			return (128 + WTERMSIG(waitstatus));
		else
			return (EXIT_SUCCESS);
	}
}


int	parent_one_command(t_exec_var *var)
{
	int	waitstatus;

	wrap_sighandler(SIGINT, SIG_IGN);
	waitpid(var->process, &waitstatus, 0);
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	heredoc_unlinker(var->cmnd_list);
	if (WIFEXITED(waitstatus))
		return (WEXITSTATUS(waitstatus));
	else if (WIFSIGNALED(waitstatus))
		return (128 + WTERMSIG(waitstatus));
	else
		return (EXIT_SUCCESS);
}
