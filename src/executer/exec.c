/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/23 16:29:39 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
				status = grandparent_process(var, j);
			else
				parent_of_grandchild(var, tmp);
			j++;
			tmp = tmp->next;
		}
		return (terminate_execvar_parent(&var), status);
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
	printf("%i\n", var.last_cmnd);
	create_all_outfiles(&var);
	if (var.last_cmnd == 1)
		return (execute_one_cmnd(&var));
	else
		return (st_execute_line(&var));
}
