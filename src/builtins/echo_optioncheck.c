/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   echo_optioncheck.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 14:34:35 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 14:35:00 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	st_optioncheck(char *option)
{
	size_t	i;

	i = 0;
	while (option[i])
	{
		if (i == 0 && option[i] != '-')
			return (false);
		if (i > 0 && option[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	echo_optioncheck(char *option)
{
	if (option == NULL)
		return (false);
	return (st_optioncheck(option));
}
