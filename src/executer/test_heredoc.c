/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_heredoc.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/25 14:54:21 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/02 13:10:30 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	display_file(char *filename)
{
	int		fd;
	char	*tmp;

	if (filename)
	{
		printf("Filename: %s\n", filename);
		fd = open(filename, O_RDONLY);
		if (fd >= 0)
		{
			tmp = get_next_line(fd);
			while (tmp != NULL)
			{
				printf("%s", tmp);
				free(tmp);
				tmp = get_next_line(fd);
			}
		}
		else
			printf("Failed to open file\n");
	}
	else
		printf("Filename is NULL\n");
	printf("\n");
}

static void	st_display_heredocs_cmnd(t_redirect *in)
{
	t_redirect	*tmp;

	if (in)
	{
		tmp = in;
		while (tmp)
		{
			if (tmp->type == HEREDOC_INFILE)
				display_file(tmp->value);
			if (tmp->type == HEREDOC_FAIL)
				printf("HEREDOC_FAIL encountered\n");
			tmp = tmp->next;
		}
	}
	else
		printf("Input files flow is empty\n");
}

void	display_heredocs(t_command *cmnd_list)
{
	t_command	*tmp;

	if (cmnd_list)
	{
		tmp = cmnd_list;
		while (tmp)
		{
			printf("Command: %s\n", (tmp->command)[0]);
			st_display_heredocs_cmnd(tmp->in);
			tmp = tmp->next;
		}
	}
}

void	test_heredoc(t_command *cmnd_list, t_htable *env)
{
	int	check;

	if (cmnd_list && env)
	{
		printf("Commencing heredoc test\n");
		check = manage_heredocs(cmnd_list, env);
		if (check == EXIT_SUCCESS)
			display_heredocs(cmnd_list);
		printf("Exit status: %i\n", check);
		heredoc_unlinker(cmnd_list);
		printf("Testing ended .....................\n");
	}
}
