/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_expandinput.c                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 19:16:15 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/03 10:10:00 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_setvars_putstr(t_heredoc_var var, int *first, int *last, int i)
{
	if (var.input[i] == 34 || var.input[i] == 39)
	{
		(*last) = i + 1;
		put_str_between(var, *first, i);
		(*first) = i;
	}
	else
	{
		(*last) = i;
		if ((*first) != i - 1)
			put_str_between(var, *first, i - 1);
		(*first) = i - 1;
	}
}

int	*skip_dollars(t_heredoc_var var, int *first, int *last)
{
	int		i;

	if (var.input == NULL || first == NULL || last == NULL)
		return (NULL);
	if ((*first) < 0)
		return (NULL);
	i = (*first) + 1;
	while (var.input[i] && var.input[i] == '$')
		i++;
	if ((*first) < i && i > 1)
		st_setvars_putstr(var, first, last, i);
	return (last);
}

char	*key_quotes(t_heredoc_var var, int *first, int *last, char ch)
{
	int		i;

	if (var.input == NULL || !(first) || !(last) || last < 0)
		return (NULL);
	if ((*first) < 0)
		return (NULL);
	i = (*first) + 1;
	while (var.input[i] && var.input[i] != ch)
		i++;
	(*last) = i + 1;
	return (give_between_vars(var.input, *first, i));
}

char	*key_noquotes(t_heredoc_var var, int *first, int *last)
{
	int		i;

	if (var.input == NULL || first == NULL || last < 0)
		return (NULL);
	if ((*first) < 0)
		return (NULL);
	i = (*first) + 1;
	while (var.input[i] && is_var_notdollar((int)(var.input[i])))
		i++;
	(*last) = i;
	return (give_between_vars(var.input, *first, i));
}
