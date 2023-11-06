/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_utils.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 12:26:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/03 10:03:17 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_between_vars(char *user_input, int first, int last)
{
	char	*rtn;

	if (user_input == NULL || first < 0 || last < 0)
		return (NULL);
	if (first >= last)
		return (NULL);
	rtn = (char *)malloc((last - first + 1) * sizeof(char));
	if (rtn == NULL)
		return (NULL);
	ft_strlcpy(rtn, (const char *)(user_input + first), last - first + 1);
	return (rtn);
}

void	put_str_between(t_heredoc_var var, int first, int last)
{
	char	*tmp;

	if (var.input && var.fd >= 0 && first >= 0 && last > 0 && first != last)
	{
		tmp = give_between_vars(var.input, first, last);
		if (tmp != NULL)
		{
			ft_putstr_fd(tmp, var.fd);
			free(tmp);
		}
		else
			ft_putstr_fd("Heredoc: Warning: malloc failed\n", STDERR_FILENO);
	}
}

static char	*st_give_key(t_heredoc_var var, int *first, int *last, int *dq)
{
	int		i;

	if (var.input == NULL || !(first) || !(dq) || last < 0)
		return (NULL);
	if ((*first) < 0)
		return (NULL);
	i = (*first);
	(*dq) = -1;
	if ((int)var.input[i] == 34 || (int)var.input[i] == 39)
	{
		(*dq) = i;
		(*first) += 1;
		return (key_quotes(var, first, last, var.input[i]));
	}
	else
		return (key_noquotes(var, first, last));
}

static char	*st_give_tmp(t_heredoc_var var, int *ecode, char *key)
{
	char	*tmp;

	if (ecode == NULL)
		return (NULL);
	if (ft_strncmp(key, "$?", ft_strlen(key) + 1) == 0)
	{
		tmp = ft_itoa(*ecode);
		(*ecode) = -1;
	}
	else if (ft_strncmp(key, "$", ft_strlen(key) + 1) != 0)
		tmp = find_env_value(var.env, key);
	else
		tmp = key;
	return (tmp);
}

void	exp_not_alldols(t_heredoc_var var, int *first, int *last, int ecode)
{
	char	*key;
	char	*tmp;
	int		dq;

	if (first && last && var.input && var.env && var.fd >= 0)
	{
		key = st_give_key(var, first, last, &dq);
		if (key != NULL)
		{
			tmp = st_give_tmp(var, &ecode, key);
			if (dq >= 0)
				write(var.fd, &(var.input[dq]), 1);
			if (tmp != NULL)
				ft_putstr_fd(tmp, var.fd);
			if (dq >= 0)
				write(var.fd, &(var.input[dq]), 1);
			if (ecode == -1 && tmp != NULL)
				free(tmp);
			free(key);
		}
		(*first) = (*last);
		(*last) = (*last) + 1;
	}
}
