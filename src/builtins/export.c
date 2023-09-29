/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:23 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/29 16:00:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef int	(*t_f_bltin)(t_exec_var, t_command);

int	export(t_exec_var *var, t_command *command)
{
	printf("\n\nyay eport, command = %s\n\n", command->command[0]);
	return (1);
}
