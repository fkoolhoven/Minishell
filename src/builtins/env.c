/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   env.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/06 14:25:59 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/06 14:29:26 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	bltin_env(t_exec_var *var, t_command *cmnd)
{
	if (var == NULL || cmnd == NULL)
		return (EXIT_FAILURE);
	else
	{
		printf("Command: ");
		if ((cmnd->command)[0] != NULL)
			printf("%s \n", (cmnd->command)[0]);
		else
			printf("(NULL) ???\n");
		return (EXIT_SUCCESS);
	}
}
