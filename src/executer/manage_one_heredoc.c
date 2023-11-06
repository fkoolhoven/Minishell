/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   manage_one_heredoc.c                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 12:27:13 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/03 10:11:09 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_h_child(char *fname, t_redirect *node, t_htable *env, int ecode)
{
	int	fd_heredoc;

	if (fname == NULL || node == NULL || env == NULL)
		exit(EXIT_FAILURE);
	fd_heredoc = open(fname, O_CREAT | O_RDWR | O_EXCL, 0644);
	if (fd_heredoc < 0)
	{
		free(fname);
		exit(EXIT_FAILURE);
	}
	else
	{
		wrap_sighandler(SIGINT, &catch_sigint_heredoc);
		wrap_sighandler(SIGQUIT, &catch_sigquit_heredoc);
		input_to_heredoc(fd_heredoc, node->value, env, ecode);
		close(fd_heredoc);
		exit(EXIT_SUCCESS);
	}
}

static void	st_set_type(int status, char *filename, t_redirect *node)
{
	if (filename != NULL && node != NULL)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == EXIT_FAILURE)
			{
				if (filename != NULL)
				{
					unlink((const char *)filename);
					free(filename);
				}
			}
			else
			{
				node->type = HEREDOC_INFILE;
				free(node->value);
				node->value = filename;
			}
		}
	}
}

static int	st_heredoc_parent(pid_t process, char *filename, t_redirect *node)
{
	int	status;

	wrap_sighandler(SIGINT, SIG_IGN);
	waitpid(process, &status, 0);
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	if (WIFSIGNALED(status))
	{
		if (filename != NULL)
		{
			unlink((const char *)filename);
			free(filename);
		}
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (st_set_type(status, filename, node), WEXITSTATUS(status));
	else
		return (EXIT_FAILURE);
}

int	man_one_here(char *fname, t_redirect *node, t_htable *env, int ecode)
{
	pid_t	process;

	if (fname == NULL || node == NULL || env == NULL)
		return (EXIT_FAILURE);
	if (env->array == NULL)
		return (free(fname), EXIT_FAILURE);
	process = fork();
	if (process < 0)
		return (free(fname), EXIT_FAILURE);
	if (process == 0)
		return (st_h_child(fname, node, env, ecode));
	else
		return (st_heredoc_parent(process, fname, node));
}
