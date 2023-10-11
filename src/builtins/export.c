/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   export.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:38:27 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/11 12:12:20 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bltin_export(t_exec_var *var, t_command *cmnd)
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
