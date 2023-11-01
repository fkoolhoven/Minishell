/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:41:37 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/30 18:04:21 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bltin_pwd(t_exec_var *var, t_command *command)
{
	int		check;

	if (var == NULL || command == NULL)
		return (EXIT_FAILURE);
	if (var->cur_path == NULL)
	{
		ft_putstr_fd("Error: current path not found\n", STDERR_FILENO);
		rl_on_new_line();
		return (EXIT_FAILURE);
	}
	check = printf("%s\n", var->cur_path);
	if (check < 0)
		return (EXIT_FAILURE);
	rl_on_new_line();
	return (EXIT_SUCCESS);
}
