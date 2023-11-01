/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_utils.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 12:26:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 10:19:07 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*st_give_between_vars(char *user_input, int first, int last)
{
	char	*rtn;

	if (user_input == NULL || first < 0 || last < 0)
		return (NULL);
	if (first >= last)
		return (NULL);
	rtn = (char *)malloc((last - first + 1) * sizeof(char)); // good
	if (rtn == NULL)
		return (NULL);
	ft_strlcpy(rtn, (const char *)(user_input + first), last - first + 1);
	return (rtn);
}

static char	*st_give_key(char *user_input, int *first, int last)
{
	int		i;

	if (user_input == NULL || first == NULL || last < 0)
		return (NULL);
	if ((*first) < 0)
		return (NULL);
	if (last == (*first) && last == 0)
		i = 1;
	else
		i = last + 1;
	while (user_input[i] && ft_isalnum((int)user_input[i]) == 1)
		i++;
	(*first) = i;
	return (st_give_between_vars(user_input, last, i));
}

void	put_str_between(t_heredoc_var var, int first, int last)
{
	char	*tmp;

	if (var.input && var.fd >= 0 && first >= 0 && last > 0)
	{
		tmp = st_give_between_vars(var.input, first, last); // good
		if (tmp != NULL)
		{
			ft_putstr_fd(tmp, var.fd);
			free(tmp);
		}
		else
			ft_putstr_fd("Heredoc: Warning: malloc failed\n", STDERR_FILENO);
	}
}

void	expand_put_var(t_heredoc_var var, int *first, int last)
{
	char	*key;
	char	*tmp;

	if (first && var.input && var.env && var.fd >= 0)
	{
		key = st_give_key(var.input, first, last); // good now
		if (key != NULL)
		{
			tmp = find_env_value(var.env, key);
			if (tmp != NULL)
				ft_putstr_fd(tmp, var.fd);
			else
				ft_putstr_fd(key, var.fd);
			free(key);
		}
	}
}
