/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/09 15:50:46 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	st_execute_one_cmnd(t_exec_var *var)
{
	int	bltin_index;

//	printf("Executing one command \n");
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
			return (exec_error_parent(var, -1));
		else 
		{
			if (var->process == 0)
				return (child_process_onecmnd(var, var->cmnd_list));
			else 
				return (parent_one_command(var));
		}
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

static int	st_execute_line(t_exec_var *var)
{
	t_command	*tmp;
	int			j;
	int			status;
	int			fd_read;

//	printf("Executing ... a lot\n");
//	printf("Amount of commands: %i \n", var->last_cmnd);
	if (var != NULL)
	{
		j = 0;
		tmp = var->cmnd_list;
		fd_read = -1;
		while (j < var->last_cmnd)
		{
//			printf("j-th command: %i\n", j);
			if (j < var->last_cmnd - 1)
			{
				if (pipe(var->fd_pipe) < 0)
					return (exec_error_parent_nopipe(var, fd_read));
			}
			var->process = fork();
			if (var->process < 0)
				return (exec_error_parent(var, fd_read));
			else if (var->process != 0)
				status = parent_process(var, j, &fd_read);
			else
				child_process(var, tmp, fd_read);
			j++;
			tmp = tmp->next;
		}
		return (status);
	}
	return (EXIT_FAILURE);
}

/* execute
   		PROBLEMS:	1.	If the environment is implemented using something different than
						char **, you need to give this struct as well, to make sure the
						builtin export, unset and env work properly
					2.	Still need to implement that you fork before calling one of the executing
						functions, because then we can use exit ... only if it is not a builtin command
						at least (in case of one command) --> also have to save exitstatus in parent somehow ..??
						2.1		or not, then you need to take care that the parent doesn't exit 
								but that it gives exitstatus without exiting process (which at that point is our shell)
					3.	...
   		To do:		1.	Write st_execute_one_cmnd()
					2.	Check whether if the commandlist is longer than one, if 
						everything has a pipe or not ... ???
					3.	Write a function to create all outfiles if they don't exist
					4.	...
		Explanation:	This function checks whether the commandlist contains
						one or more commands and thus decides which function to
						run to execute the input
   */

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
	var.last_cmnd = size_cmndlist(cmnd_list);
	create_all_outfiles(&var);
	if (var.last_cmnd == 1)
		return (st_execute_one_cmnd(&var));
	else
		return (st_execute_line(&var));
} /*
int	execute(t_command *cmnd_list, t_htable *environ, int exit_status)
{
	t_exec_var	var;
	int			fd[2];
	int			waitstatus;
	pid_t		process;

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
	var.last_cmnd = size_cmndlist(cmnd_list);
	create_all_outfiles(&var);
	process = fork();
	if (process < 0)
		return (EXIT_FAILURE);
	if (process == 0)
	{
		if (var.last_cmnd == 1)
			exit(st_execute_one_cmnd(&var));
		else
			exit(st_execute_line(&var));
	}
	else
	{
		printf("In minishell parent\n");
		wrap_sighandler(SIGINT, SIG_IGN);
		waitpid(process, &waitstatus, 0);
		waitpid(0, NULL, 0);
		wrap_sighandler(SIGINT, &catch_sigint_parent);
		printf("Going to return status\n");
		if (WIFEXITED(waitstatus))
			return (WEXITSTATUS(waitstatus));
		else if (WIFSIGNALED(waitstatus))
			return (128 + WTERMSIG(waitstatus));
		else
			return (EXIT_SUCCESS);
	}
} */
