/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 13:32:56 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/15 16:51:45 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
// size_cmndlist returns the amount of commands in cmnd_list
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

static void	st_open_file_failed(t_redirect *node)
{
	if (node != NULL)
	{
		ft_putstr_fd("\t Warning: Opening of file ", 2);
		ft_putstr_fd(node->value, 2);
		ft_putstr_fd(" failed \n", 2);
	}
	else
		ft_putstr_fd("\t Warning: Filename is (NULL)\n", 2);
}

/* give_input_fd
   		To do:		1.	Shorten the function
					2.	...
		Explanation:	This function iterates through the redirect list for input
						and returns the last file it should use as input
   */
int	give_input_fd(t_redirect *in)
{
	int			fd_prv;
	int			fd_cur;
	t_redirect	*tmp;

	if (in == NULL)
		return (-1);
	tmp = in;
	fd_cur = -2;
	while (tmp != NULL)
	{
		fd_prv = fd_cur;
		if (tmp->type == INFILE || tmp->type == HEREDOC_INFILE)
		{
			fd_cur = open(tmp->value, O_RDONLY);
			if (fd_cur >= 0)
				close(fd_prv);
			else
			{
				fd_cur = fd_prv;
				st_open_file_failed(tmp);
			}
		}
		if (tmp->type == PIPE)
		{
			if (tmp->next == NULL && fd_cur == -2)
				return (fd_cur);
			if (fd_cur >= 0 && tmp->next != NULL)
				return (fd_cur);
		}
		tmp = tmp->next;
	}
	return (fd_cur);
}

/* give_output_fd
   			To do:		1.	Shorten function
						2.	...
			Explanation:	This function iterates through the redirect list and
							searches for the last node with a valid output file
							It assumes all the output files already exist!!!
   */
int	give_output_fd(t_redirect *out)
{
	int			fd_prv;
	int			fd_cur;
	t_redirect	*tmp;

	if (out == NULL)
		return (-1);
	tmp = out;
	fd_cur = -2;
	while (tmp != NULL)
	{
		fd_prv = fd_cur;
		if (tmp->type == OUTFILE)
		{
			fd_cur = open(tmp->value, O_WRONGLY | O_TRUNC);
			if (fd_cur >= 0)
				close(fd_prv);
			else
			{
				fd_cur = fd_prv;
				st_open_file_failed(tmp);
			}
		}
		if (tmp->type == OUTFILE_APPEND)
		{
			fd_cur = open(tmp->value, O_WRONGLY);
			if (fd_cur >= 0)
				close(fd_prv);
			else
			{
				fd_cur = fd_prv;
				st_open_file_failed(tmp);
			}
		}
		if (tmp->type == PIPE)
			return (fd_cur);
		tmp = tmp->next;
	}
}

static void	st_unlink_heredoc_input(t_redirect *in)
{
	if (in != NULL)
	{
		while (in != NULL)
		{
			if (in->type == HEREDOC_INFILE)
				unlink((const char *)(in->value));
			in = in->next;
		}
	}
}

/* heredoc_unlinker
   		To do: 		1.	Decide where to use it
					2. 	...
		Explanation:	This function iterates through the command list
						and checks per command if the input redirect list contains
						HEREDOC_INFILES, if it does it unlinks these files. 
   */
void heredoc_unlinker(t_command *command_list)
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
