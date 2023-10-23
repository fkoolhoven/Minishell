/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   errors_exec_swap.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 12:38:02 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/23 12:38:17 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_error_child(int fd_in, int fd_out, t_exec_var *var)
{
	if (fd_in >= 3)
		close(fd_in);
	if (fd_out >= 3)
		close(fd_out);
	terminate_execvar_child(&var);
	perror(NULL);
	return (EXIT_FAILURE);
}

int	swap_error_parent(int fd_in, int fd_out, t_exec_var *var)
{
	if (fd_in >= 3)
		close(fd_in);
	if (fd_out >= 3)
		close(fd_out);
	terminate_execvar_parent(&var);
	perror(NULL);
	return (EXIT_FAILURE);
}
