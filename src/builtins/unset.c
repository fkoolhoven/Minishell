/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:00 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/20 11:32:14 by fkoolhov         ###   ########.fr       */
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
		{
			ft_putstr_fd("export: unable to unset ", STDERR_FILENO);
			ft_putendl_fd(command[i], STDERR_FILENO);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
