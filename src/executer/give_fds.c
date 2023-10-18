/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   give_fds.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:25:16 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/18 12:51:54 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	st_open_file_failed(t_redirect *node)
{
	if (node != NULL)
	{
		if (node->value != NULL && node->next != NULL)
		{
			ft_putstr_fd("\t Warning: Opening of file ", 2);
			ft_putstr_fd(node->value, 2);
			ft_putstr_fd(" failed \n", 2);
		}
		else if (node->next != NULL)
			ft_putstr_fd("\t Warning: Filename is (NULL)\n", 2);
	}
	else
		ft_putstr_fd("\t Warning: Redirect node is (NULL)\n", 2);
}

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
		if (fd >= 3)
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

static void	st_change_fd(t_redirect *tmp, int *fd)
{
	if (tmp != NULL && fd != NULL)
	{
		if (tmp->type == OUTFILE)
		{
			(*fd) = open(tmp->value, O_WRONLY | O_TRUNC);
			if (*fd < 0)
				st_open_file_failed(tmp);
		}
		else if (tmp->type == OUTFILE_APPEND)
		{
			(*fd) = open(tmp->value, O_WRONLY | O_APPEND);
			if (*fd < 0)
				st_open_file_failed(tmp);
		}
	}
}

int	give_output_fd(t_redirect *out)
{
	int			fd;
	t_redirect	*tmp;

	if (out == NULL)
		return (-3);
	tmp = out;
	fd = -2;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			return (fd);
		if (fd >= 3)
			close(fd);
		st_change_fd(tmp, &fd);
		tmp = tmp->next;
	}
	return (fd);
}
