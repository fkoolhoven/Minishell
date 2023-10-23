/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_fds.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:25:40 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/23 11:53:11 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_swap_stdin(t_exec_var *var, int fd_in, int fd_out)
{
	if (fd_in == -1)
		return (swap_error_child(fd_in, fd_out, var));
	if (fd_in >= 0)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (swap_error_child(fd_in, fd_out, var));
		if (fd_in >= 3)
			close(fd_in);
	}
	else if (var->fd_read >= 0)
	{
		if (dup2(var->fd_read, STDIN_FILENO) < 0)
			return (swap_error_child(fd_in, fd_out, var));
	}
	return (EXIT_SUCCESS);
}

static int	st_swap_stdout(t_exec_var *var, int fd_out)
{
	if (fd_out == -1)
		return (swap_error_child(-1, fd_out, var));
	if (fd_out >= 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (swap_error_child(-1, fd_out, var));
		if (fd_out >= 3)
			close(fd_out);
	}
	if (fd_out == -2)
	{
		if (dup2(var->fd_pipe[1], STDOUT_FILENO) < 0)
			return (swap_error_child(-1, fd_out, var));
	}
	return (EXIT_SUCCESS);
}

int	swap_filedescriptors(t_exec_var *var, t_command *cmnd)
{
	int	fd_in;
	int	fd_out;
	int	check;

	if (var == NULL)
		return (EXIT_FAILURE);
	fd_out = give_output_fd(cmnd->out);
	check = st_swap_stdout(var, fd_out);
	if (check != EXIT_SUCCESS)
		return (check);
	fd_in = give_input_fd(cmnd->in);
	check = st_swap_stdin(var, fd_in, fd_out);
	if (check != EXIT_SUCCESS)
		return (check);
	if (var->fd_read >= 3)
		close(var->fd_read);
	close(var->fd_pipe[0]);
	close(var->fd_pipe[1]);
	return (EXIT_SUCCESS);
}
