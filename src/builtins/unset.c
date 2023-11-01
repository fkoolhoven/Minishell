/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:00 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/01 12:20:33 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bltin_unset(t_exec_var *var, t_command *command_struct)
{
	char	**command;
	int		i;

	command = command_struct->command;
	i = 1;
	while (command[i])
	{
		if (delete_pair(var->env, command[i]) < 0)
			return (minishell_error_return_failure("unable to unset"));
		i++;
	}
	return (EXIT_SUCCESS);
}
