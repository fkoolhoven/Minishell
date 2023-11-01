/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:41:54 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 13:39:49 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	st_error(t_exec_var *var)
{
	ft_putstr_fd("Error: making pid list failed\n", STDERR_FILENO);
	return (var->last_cmnd);
}

static int	st_exec_cmnds(t_exec_var *var)
{
	t_command	*tmp;
	int			j;
	int			status;

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
			status = parent_process(var, j);
		else
			child_process(var, tmp);
		if (var->process_lst == NULL && j >= 1)
			j = st_error(var);
		j++;
		tmp = tmp->next;
	}
	return (terminate_execvar_parent(&var), status);
}

static int	st_execute_line(t_exec_var *var)
{
	if (var != NULL)
		return (st_exec_cmnds(var));
	return (EXIT_FAILURE);
}

static int	st_initvar(t_exec_var *var, t_htable *env, t_command *cmnd_list)
{
	if (var == NULL || cmnd_list == NULL || env == NULL)
		return (EXIT_FAILURE);
	var->cmnd_list = cmnd_list;
	var->env = env;
	var->process = -1;
	var->process_lst = NULL;
	var->last_cmnd = size_cmndlist(cmnd_list);
	var->env_str = convert_htable_to_strarray(env);
	if (var->env_str == NULL)
	{
		ft_putstr_fd("Error: converting hashtable failed\n", STDERR_FILENO);
		return (terminate_execvar_parent(&var), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	execute(t_command *cmnd_list, t_htable *env, int estatus, char *cpath)
{
	t_exec_var	var;
	int			fd[2];
	int			prev_pipe[2];

	if (cmnd_list == NULL || env == NULL || cpath == NULL)
		return (EXIT_FAILURE);
	var.cur_path = cpath;
	fd[0] = -1;
	fd[1] = -1;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	var.fd_pipe = fd;
	var.exit_status = estatus;
	var.prev_pipe = prev_pipe;
	if (st_initvar(&var, env, cmnd_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_all_outfiles(&var);
	if (var.last_cmnd == 1)
		return (execute_one_cmnd(&var));
	else
		return (st_execute_line(&var));
}
