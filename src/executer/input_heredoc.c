/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   input_heredoc.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/25 12:52:55 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/25 17:51:50 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* bij $$ expand het naar ibusibus --> WAAROM???? */

static char	*st_give_between_vars(char *user_input, int first, int last)
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

static void	st_put_str_between(int fd, char *user_input, int first, int last)
{
	char	*tmp;

	if (user_input && fd >= 0 && first >= 0 && last >= 0)
	{
		tmp = st_give_between_vars(user_input, first, last);
		if (tmp != NULL)
		{
			ft_putstr_fd(tmp, fd);
			free(tmp);
		}
	}
}

static void	st_expand_put_var(int fd, char *user_input, int *first, int last, t_htable *env)
{
	char	*key;
	char	*tmp;

	if (first && user_input && env && fd >= 0)
	{
		key = st_give_key(user_input, first, last);
		if (key != NULL)
		{
			tmp = find_env_value(env, key);
			if (tmp != NULL)
				ft_putstr_fd(tmp, fd);
			else
				ft_putstr_fd(key, fd);
			free(key);
		}
	}
}

/* Weird things happening here, it seems not to return to the original heredoc_handler function
   This is a problem because it ends up being an infinite loop. */

void	add_expanded_input(int fd, char *user_input, t_htable *env)
{
	int		i;
	int		first;
	int		last;

	if (fd >= 0 && user_input && env)
	{
		i = 0;
		first = 0;
		while (user_input[i])
		{
			if (user_input[i] == '$')
			{
				last = i;
				st_put_str_between(fd, user_input, first, last);
				st_expand_put_var(fd, user_input, &first, last, env);
				i = first - 1;
			}
			else if (user_input[i + 1] == '\0')
				st_put_str_between(fd, user_input, first, i + 1);
			i++;
		}
		ft_putstr_fd("\n", fd);
	}
}
