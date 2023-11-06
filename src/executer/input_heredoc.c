/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   input_heredoc.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 12:27:04 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/03 10:04:37 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_found_dollar(t_heredoc_var var, int ecode, int *first, int *last)
{
	int	*check;

	if (first && last)
	{
		put_str_between(var, *first, *last);
		(*first) = (*last);
		(*last) = (*first) + 1;
		check = skip_dollars(var, first, last);
		if (check != NULL)
			exp_not_alldols(var, first, last, ecode);
		return ((*last) - 1);
	}
	return (0);
}

static void	st_expand_input(t_heredoc_var var, int ecode)
{
	int	i;
	int	first;
	int	last;
	int	check;

	if (var.fd >= 0 && var.input && var.env)
	{
		i = 0;
		first = 0;
		while (var.input[i])
		{
			if (var.input[i] == '$')
			{
				last = i;
				check = st_found_dollar(var, ecode, &first, &last);
				if (check >= 0)
					i = check;
			}
			else if (var.input[i + 1] == '\0')
				put_str_between(var, first, i + 1);
			i++;
		}
		ft_putstr_fd("\n", var.fd);
	}
}

static void	st_add_exp_input(int fd, char *user_input, t_htable *env, int ecode)
{
	t_heredoc_var	here_var;

	if (fd >= 0 && user_input && env)
	{
		here_var.fd = fd;
		here_var.input = user_input;
		here_var.env = env;
		st_expand_input(here_var, ecode);
	}
}

void	input_to_heredoc(int fd, char *limit, t_htable *env, int ecode)
{
	char	*user_input;
	int		i;

	i = 1;
	while (i == 1)
	{
		user_input = readline("\t» ");
		if (!(user_input))
			i = -1;
		else if (ft_strncmp(user_input, limit, ft_strlen(limit) + 1) == 0)
			i = 0;
		else if (ft_strchr((const char *)user_input, '$') != NULL)
			st_add_exp_input(fd, user_input, env, ecode);
		else
		{
			ft_putstr_fd(user_input, fd);
			ft_putstr_fd("\n", fd);
		}
		free(user_input);
	}
}
