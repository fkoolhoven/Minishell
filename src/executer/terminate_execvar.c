/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   terminate_execvar.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/09 16:09:28 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/09 16:12:32 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	terminate_execvar(t_exec_var *var)
{
	if (var != NULL)
	{
		if (var->env_str != NULL)
			ft_free_str_array(var->env_str);
		if (var->fd_pipe != NULL)
		{
			if ((var->fd_pipe)[0] >= 3)
				close((var->fd_pipe)[0]);
			if ((var->fd_pipe)[1] >= 3)
				close((var->fd_pipe)[1]);
		}
		if (var->fd_read >= 3)
			close(var->fd_read);
	}
}
