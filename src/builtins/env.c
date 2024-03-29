/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:45:17 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/11 12:44:32 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bltin_env(t_exec_var *var, t_command *command_struct)
{
	(void)command_struct;
	ft_putstr_array_fd(var->env_str, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
