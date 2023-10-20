/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   swap_fd_mini.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/20 10:11:34 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/20 12:21:27 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_swap_stdin(t_exec_var *var, int fd_in, int fd_out)
{
	if (fd_in >= 0)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (exec_error_swap(fd_in, fd_out, var));
		if (fd_in >= 3)
			close(fd_in);
	}
	if (fd_in == -1)
		return (exec_error_swap(fd_in, fd_out, var));
	return (EXIT_SUCCESS);
}

static int	st_swap_stdout(t_exec_var *var, int fd_out)
{
	if (fd_out == -1)
		return (exec_error_swap(-1, fd_out, var));
	if (fd_out >= 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (exec_error_swap(-1, fd_out, var));
		if (fd_out >= 3)
			close(fd_out);
	}
	return (EXIT_SUCCESS);
}

int	swap_mini(t_exec_var *var, t_command *cmnd, int *fd_in, int *fd_out)
{
	int	in;
	int	out;
	int	check;

	if (var == NULL || fd_out == NULL || fd_in == NULL)
		return (EXIT_FAILURE);
	(*fd_in) = dup(STDIN_FILENO);
	(*fd_out) = dup(STDOUT_FILENO);
	if ((*fd_in) < 0 || (*fd_out) < 0)
		return (exec_error_swap(-1, -1, var));
	out = give_output_fd(cmnd->out);
	check = st_swap_stdout(var, out);
	if (check != EXIT_SUCCESS)
		return (check);
	in = give_input_fd(cmnd->in);
	check = st_swap_stdin(var, in, out);
	if (check != EXIT_SUCCESS)
		return (check);
	if (var->fd_read >= 3)
		close(var->fd_read);
	return (EXIT_SUCCESS);
}

int	swap_back_in_minishell(t_exec_var *var, int fd_stdin, int fd_stdout)
{
	if (var == NULL)
		return (EXIT_FAILURE);
	if (dup2(fd_stdin, STDIN_FILENO) < 0)
		return (exec_error_swap(fd_stdin, fd_stdout, var));
	if (dup2(fd_stdout, STDOUT_FILENO) < 0)
		return (exec_error_swap(fd_stdin, fd_stdout, var));
	close(fd_stdout);
	close(fd_stdin);
	return (EXIT_SUCCESS);
}
