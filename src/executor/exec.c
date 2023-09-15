/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/15 16:52:38 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* Childprocess: 
   		To add: 	1.	distinction between builtins and other commands
					2.	get correct path for command
					3.	...
		Explanation:	The function first finds the correct input and output streams
						If fd_in >= 0, then we know that there is an input file and 
							we need to change the stdin
						If fd_in < 0, then we know that either there is a pipe or 
							input was NULL, since stdin has been changed in parent
							we don't need to adjust it anymore
						If fd_out >= 0, then we know that an output file exists and 
							we need to change stdout to this file
						If fd_out == -1, then we know there were no output files or pipes
							this means that stdout does not need to be changed
						If fd_out == -2, then we know that there is a pipe and
							we need to change stdout to the pipe
						Now we have changed the stdout and stdin as necessary,
							we can close the pipefd and move on
						...
						We need to add that if command is a builtin that we call the
							appropriate function
							and if it is not a builtin execve is called with appropriate
							path
						...

   */
void	child_process(t_exec_var *var, t_command *cmnd, int j)
{
	int	fd_in;
	int	fd_out;

	if (var != NULL && cmnd != NULL)
	{
		fd_in = give_input_fd(cmnd->in);
		fd_out = give_output_fd(cmnd->out);
		if (fd_in >= 0)
		{
			if (dup2(fd_in, STDIN_FILENO) < 0)
				exec_error_handler(...);
			close(fd_in);
		}
		if (fd_out >=0)
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				exec_error_handler(...);
			close(fd_out);
		}
		if (fd_out == -2)
		{
			if (dup2(var->pipe_fd[1], STDOUT_FILENO) < 0)
				exec_error_handler(...);
		}
		close(var->pipe_fd[0]);
		close(var->pipe_fd[1]);
		
	}
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

void	parent_process(t_exec_var *var, int j)
{
	int	waitstatus;

	if (j != var->last_cmnd)
	{
		if (dup2(var->fd_pipe[0], STDIN_FILENO) < 0)
			exec_error_handler(...);
		close(var->fd_pipe[0]);
		close(var->fd_pipe[1]);
	}
	else if (j == var->last_cmnd)
	{
		waitpid(var->process, &waitstatus, 0);
		heredoc_unlinker(var->cmnd_list);
		if (WIFEXITED(waitstatus))
			exit(WEXITSTATUS(waitstatus));
		else if (WIFSIGNALED(waitstatus))
			exit(128 + WTERMSIG(waitstatus));
		else
			exit(EXIT_SUCCESS);
	}
}

/* st_execute_line
   			To do:		1.	Write exec_error_handler
						2.	...
			Explanation:	This function iterates through the command list,
								creating pipes, forking and 
								putting the childprocess to work to execute command
								and parent to continue or wait for other processes
   */

static void	st_execute_line(t_exec_var *var)
{
	t_command	*tmp;
	int			j;

	if (var != NULL)
	{
		j = 0;
		tmp = var->cmnd_list;
		while (tmp != NULL)
		{
			if (j < var->last_cmnd)
			{
				if (pipe(var->fd_pipe) < 0)
					exec_error_handler(...);
			}
			var->process = fork();
			if (var->process < 0)
				exec_error_handler(...);
			else if (var->process == 0)
				child_process(var, tmp, j);
			else
				parent_process(var, j);
			j++;
			tmp = tmp->next;
		}
	}
	exit(EXIT_FAILURE);
}

/* execute
   		To do:		1.	Write st_execute_one_cmnd()
					2.	Check whether if the commandlist is longer than one, if 
						everything has a pipe or not ... ???
					3.	Write a function to create all outfiles if they don't exist
					4.	...
		Explanation:	This function checks whether the commandlist contains
						one or more commands and thus decides which function to
						run to execute the input
   */

int	execute(t_command *cmnd_list, char **environ)
{
	t_exec_var	var;
	int			fd[2];

	if (cmnd_list != NULL && environ != NULL)
	{
		var.cmnd_list = cmnd_list;
		var.env = environ;
		var.fd_pipe = fd;
		var.process = 1;
		var.last_cmnd = st_size_cmndlist(cmnd_list);
		if (var.last_cmnd == 1)
			st_execute_one_cmnd(&var);
		else
			st_execute_line(&var);
	}
	exit(EXIT_FAILURE);
}
