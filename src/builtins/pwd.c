/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pwd.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/20 09:41:37 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/06 14:56:31 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	bltin_pwd(t_exec_var *var, t_command *command)
{
	char	*path;
	int		check;

	if (var == NULL || command == NULL)
		return (EXIT_FAILURE);
	path = getcwd(NULL, 0);
	rl_on_new_line();
	if (path == NULL)
	{
		ft_putstr_fd("Error: path not found\n", 2);
		rl_on_new_line();
		return (EXIT_FAILURE);
	}
	check = printf("%s\n", path);
	if (check < 0)
		return (EXIT_FAILURE);
	rl_on_new_line();
	return (EXIT_SUCCESS);
}
