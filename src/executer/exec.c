/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/29 14:23:41 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	st_execute_one_cmnd(t_exec_var *var)
{
	int	bltin_index;

	if (var != NULL)
	{
		if (var->cmnd_list != NULL)
		{
			bltin_index = check_if_builtin(var, var->cmnd_list);
			if (bltin_index >= 0)
				exit(execute_builtin(var, var->cmnd_list, bltin_index));
			else
			{
				var->process = fork();
				if (var->process < 0)
					exec_error_handler(...);
				else if (var->process == 0)
					child_process(var, var->cmnd_list);
				else 
					parent_one_command(var);
			}
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
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
				child_process(var, tmp);
			else
				parent_process(var, j);
			j++;
			tmp = tmp->next;
		}
	}
	exit(EXIT_FAILURE);
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

int	execute(t_command *cmnd_list, t_htable *environ)
{
	t_exec_var	var;
	int			fd[2];

	if (cmnd_list != NULL && environ != NULL)
	{
		var.cmnd_list = cmnd_list;
		var.env = environ;
		var.env_str = convert_htable_to_strarray(environ); 
		if (var.env_str == NULL)
			return (EXIT_FAILURE);
		var.fd_pipe = fd;
		var.process = 1;
		var.last_cmnd = size_cmndlist(cmnd_list);
		create_all_outfiles(&var);
		manage_heredocs(cmnd_list, environ);
		if (var.last_cmnd == 1)
			return (st_execute_one_cmnd(&var));
		else
			return (st_execute_line(&var));
	}
	return (EXIT_FAILURE);
}
