/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_bool.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 18:24:56 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 19:03:16 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	input_is_all_dollars(char *input)
{
	size_t	i;

	if (input == NULL)
		return (false);
	i = 0;
	while (input[i])
	{
		if (input[i] != '$')
			return (false);
		i++;
	}
	return (true);
}

bool	is_var_notdollar(int c)
{
	if (c == '$')
		return (false);
	if (ft_isalnum(c) == 1)
		return (true);
	if (c == '?')
		return (true);
	else
		return (false);
}
