/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_unlinker.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 13:03:07 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/27 15:45:50 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_unlink_heredoc_input(t_redirect *in)
{
	if (in != NULL)
	{
		while (in != NULL)
		{
			if (in->type == HEREDOC_INFILE)
			{
				in->type = HEREDOC_UNLINKED;
				unlink((const char *)(in->value));
			}
			in = in->next;
		}
	}
}

void	heredoc_unlinker(t_command *command_list)
{
	t_command	*tmp;

	if (command_list != NULL)
	{
		tmp = command_list;
		while (tmp)
		{
			st_unlink_heredoc_input(tmp->in);
			tmp = tmp->next;
		}
	}
}
