/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   echo.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 15:42:44 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/18 15:57:53 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	st_echo_n(t_command *command)
{
	int		i;
	int		check;
	char	**cmnd;

	i = 2;
	cmnd = command->command;
	while (cmnd[i])
	{
		check = printf(cmnd[i]);
		if (check < 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCES);
}

static int	st_echo(t_command *command)
{
	int		i;
	int		check;
	char	**cmnd;

	i = 2;
	cmnd = command->command;
	while (cmnd[i])
	{
		check = printf(cmnd[i]);
		if (check < 0)
			return (EXIT_FAILURE);
		i++;
	}
	check = printf("\n");
	if (check < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCES);
}

int	bltint_echo(t_exec_var *var, t_command *command)
{
	if (var == NULL || command == NULL)
		return (EXIT_FAILURE);
	if (command->command == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp((command->command)[1], "-n", 2) == 0)
		return (st_echo_n(command));
	else 
		return (st_echo(command));
}
