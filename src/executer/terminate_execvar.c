/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   terminate_execvar.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:25:59 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/23 12:28:11 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	terminate_execvar_parent(t_exec_var **var)
{
	if (var != NULL)
	{
		if (*var != NULL)
		{
			if ((*var)->env_str != NULL)
				ft_free_str_array((*var)->env_str);
			if ((*var)->fd_pipe != NULL)
			{
				if (((*var)->fd_pipe)[0] >= 3)
					close(((*var)->fd_pipe)[0]);
				if (((*var)->fd_pipe)[1] >= 3)
					close(((*var)->fd_pipe)[1]);
			}
			if ((*var)->fd_read >= 3)
				close((*var)->fd_read);
			if ((*var)->cmnd_list != NULL)
			{
				heredoc_unlinker((*var)->cmnd_list);
				terminate_command_list(&((*var)->cmnd_list));
			}
			(*var) = NULL;
		}
	}
}

void	terminate_execvar_child(t_exec_var **var)
{
	if (var != NULL)
	{
		if (*var != NULL)
		{
			if ((*var)->env_str != NULL)
				ft_free_str_array((*var)->env_str);
			if ((*var)->fd_pipe != NULL)
			{
				if (((*var)->fd_pipe)[0] >= 3)
					close(((*var)->fd_pipe)[0]);
				if (((*var)->fd_pipe)[1] >= 3)
					close(((*var)->fd_pipe)[1]);
			}
			if ((*var)->fd_read >= 3)
				close((*var)->fd_read);
			if ((*var)->cmnd_list != NULL)
				terminate_command_list(&((*var)->cmnd_list));
			if ((*var)->env != NULL)
				terminate_hashtable((*var)->env);
			(*var) = NULL;
		}
	}
}

void	terminate_execvar_exit(t_exec_var **var)
{
	if (var != NULL)
	{
		if (*var != NULL)
		{
			if ((*var)->env_str != NULL)
				ft_free_str_array((*var)->env_str);
			if ((*var)->fd_pipe != NULL)
			{
				if (((*var)->fd_pipe)[0] >= 3)
					close(((*var)->fd_pipe)[0]);
				if (((*var)->fd_pipe)[1] >= 3)
					close(((*var)->fd_pipe)[1]);
			}
			if ((*var)->fd_read >= 3)
				close((*var)->fd_read);
			if ((*var)->cmnd_list != NULL)
			{
				heredoc_unlinker((*var)->cmnd_list);
				terminate_command_list(&((*var)->cmnd_list));
			}
			if ((*var)->env != NULL)
				terminate_hashtable((*var)->env);
			(*var) = NULL;
		}
	}
}
