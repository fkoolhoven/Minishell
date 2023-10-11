/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:00 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/11 12:33:36 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_exec_var *var, t_command *command_struct)
{
	char	**command;
	int		i;

	command = command_struct->command;
	i = 1;
	if (!command[i])
		return (EXIT_FAILURE);
	while (command[i])
	{
		delete_pair(var->env, command[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
