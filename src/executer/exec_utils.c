/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 13:32:56 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/06 15:09:21 by jhendrik      ########   odam.nl         */
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
		if (node->value != NULL)
		{
			ft_putstr_fd("\t Warning: Opening of file ", 2);
			ft_putstr_fd(node->value, 2);
			ft_putstr_fd(" failed \n", 2);
		}
		else
			ft_putstr_fd("\t Warning: Filename is (NULL)\n", 2);
	}
	else
		ft_putstr_fd("\t Warning: Redirect node is (NULL)\n", 2);
}

/* give_input_fd
   		To do:		1.	Shorten the function
					2.	...
		Explanation:	This function iterates through the redirect list for input
						and returns the last file it should use as input
   */
/* int	give_input_fd(t_redirect *in)
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
} */

int	give_input_fd(t_redirect *in)
{
	int			fd;
	t_redirect	*tmp;

	if (in == NULL)
		return (-1);
	tmp = in;
	fd = -2;
	while (tmp != NULL)
	{
		if (fd >= 0)
			close(fd);
		if (tmp->type == INFILE || tmp->type == HEREDOC_INFILE)
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd < 0)
				st_open_file_failed(tmp);
		}
		tmp = tmp->next;
		if (tmp == NULL)
			return (fd);
	}
	return (fd);
}

/* give_output_fd
   			To do:		1.	Shorten function
						2.	...
			Explanation:	This function iterates through the redirect list and
							searches for the last node with a valid output file
							It assumes all the output files already exist!!!
   */
/* int	give_output_fd(t_redirect *out)
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
} */

int	give_output_fd(t_redirect *out)
{
	int			fd;
	t_redirect	*tmp;

	if (out == NULL)
		return (-1);
	tmp = out;
	fd = -2;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			return (fd);
		if (fd >= 0)
			close(fd);
		if (tmp->type == OUTFILE)
		{
			fd = open(tmp->value, O_WRONLY | O_TRUNC);
			if (fd < 0)
				st_open_file_failed(tmp);
		}
		else if (tmp->type == OUTFILE_APPEND)
		{
			fd = open(tmp->value, O_WRONLY);
			if (fd < 0)
				st_open_file_failed(tmp);
		}
		tmp = tmp->next;
	}
	return (fd);
}
/* swap_filedescriptors: 
		To check:		1. if it actually works
						2. if it closes everything
						3. ...
		Explanation:	The function first finds the correct input and output streams
						If fd_in >= 0, then we know that there is an input file and 
							we need to change the stdin
						If fd_in < 0, then we know that either there is a pipe or 
							input was NULL, since stdin has been changed in parent
							we don't need to adjust it anymore
						If fd_out >= 0, then we know that an output file exists and 
							we need to change stdout to this file
						If fd_out == -1, then we know there were no output files or pipes
							this means that stdout does not need to be changed
						If fd_out == -2, then we know that there is a pipe and
							we need to change stdout to the pipe
						Now we have changed the stdout and stdin as necessary,
							we can close the pipefd and move on
   */
int	swap_filedescriptors(t_exec_var *var, t_command *cmnd)
{
	int	fd_in;
	int	fd_out;

	fd_in = give_input_fd(cmnd->in);
	fd_out = give_output_fd(cmnd->out);
	if (fd_in >= 0)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (exec_error_swap(fd_in, fd_out, var->fd_pipe));
		close(fd_in);
	}
	if (fd_out >= 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (exec_error_swap(-1, fd_out, var->fd_pipe));
		close(fd_out);
	}
	if (fd_out == -2)
	{
		if (dup2(var->fd_pipe[1], STDOUT_FILENO) < 0)
			return (exec_error_swap(-1, fd_out, var->fd_pipe));
	}
	close(var->fd_pipe[0]);
	close(var->fd_pipe[1]);
	return (EXIT_SUCCESS);
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
				if (fd != -1)
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
