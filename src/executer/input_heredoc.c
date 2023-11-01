/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   input_heredoc.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 12:27:04 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 10:16:00 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* bij $$ expand het naar ibusibus --> WAAROM???? */

static void	st_expand_input(t_heredoc_var var)
{
	int				i;
	int				first;
	int				last;

	if (var.fd >= 0 && var.input && var.env)
	{
		i = 0;
		first = 0;
		while (var.input[i])
		{
			if (var.input[i] == '$')
			{
				last = i;
				put_str_between(var, first, last);
				expand_put_var(var, &first, last);
				if (first > 1)
					i = first - 1;
				else
					i++;
			}
			else if (var.input[i + 1] == '\0')
				put_str_between(var, first, i + 1);
			i++;
		}
		ft_putstr_fd("\n", var.fd);
	}
}

static void	st_add_expanded_input(int fd, char *user_input, t_htable *env)
{
	t_heredoc_var	here_var;

	if (fd >= 0 && user_input && env)
	{
		here_var.fd = fd;
		here_var.input = user_input;
		here_var.env = env;
		st_expand_input(here_var);
	}
}

void	input_to_heredoc(int fd, char *limit, t_htable *env)
{
	char	*user_input;
	int		i;

	i = 1;
	while (i == 1)
	{
		user_input = readline(BOLDCYAN"\t» "OFF);
		if (!(user_input))
			i = -1;
		else if (ft_strncmp(user_input, limit, ft_strlen(limit) + 1) == 0)
			i = 0;
		else if (ft_strchr((const char *)user_input, '$') != NULL)
			st_add_expanded_input(fd, user_input, env);
		else
		{
			ft_putstr_fd(user_input, fd);
			ft_putstr_fd("\n", fd);
		}
		free(user_input);
	}
}
