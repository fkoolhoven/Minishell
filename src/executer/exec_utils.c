/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 13:32:56 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/09 17:28:08 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_cmndlist(t_command *cmnd_list)
{
	int	i;

	if (cmnd_list == NULL)
		return (0);
	i = 0;
	while (cmnd_list != NULL)
	{
		cmnd_list = cmnd_list->next;
		i++;
	}
	return (i);
}

static void	st_create_outfile_cmnd(t_redirect *out)
{
	int			fd;
	t_redirect	*tmp;

	if (out != NULL)
	{
		tmp = out;
		while (tmp)
		{
			if (tmp->type == OUTFILE || tmp->type == OUTFILE_APPEND)
			{
				if (access(tmp->value, F_OK) != 0)
					fd = open(tmp->value, O_CREAT | O_EXCL, 0644);
				else
					fd = -1;
				if (fd != -1 && fd >= 3)
					close(fd);
			}
			tmp = tmp->next;
		}
	}
}

void	create_all_outfiles(t_exec_var *var)
{
	t_command	*command;

	if (var != NULL)
	{
		if (var->cmnd_list != NULL)
		{
			command = var->cmnd_list;
			while (command)
			{
				st_create_outfile_cmnd(command->out);
				command = command->next;
			}
		}
	}
}
