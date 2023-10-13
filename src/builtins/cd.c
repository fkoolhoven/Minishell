/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:37:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/13 14:07:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_give_args_count(char **command)
{
	int	argc;

	if (command == NULL)
		return (-1);
	argc = 0;
	while (command[argc])
		argc++;
	return (argc);
}

static int	st_go_home()
{

}

int	bltin_cd(t_exec_var *var, t_command *cmnd)
{
	int	argc;

	if (var == NULL || cmnd == NULL)
		return (EXIT_FAILURE);
	argc = st_give_args_count(cmnd->command);
	if (argc > 2)
	{
		ft_putstr_fd((cmnd->command)[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	
}
