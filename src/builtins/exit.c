/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:38:10 by jhendrik          #+#    #+#             */
/*   Updated: 2023/11/20 11:24:42 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all_allocated_memory(t_exec_var *var)
{
	if (var->process != 0)
		terminate_execvar_exit(&var);
	else
		terminate_execvar_child(&var);
}

static bool	arg_is_numeric(char *str)
{
	bool	found_digit;
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (ft_isdigit(str[i]))
		found_digit = true;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0' && found_digit)
		return (true);
	else
		return (false);
}

static int	get_argc(char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	return (argc);
}

int	bltin_exit(t_exec_var *var, t_command *command)
{
	char	**full_command;
	int		argc;
	int		exit_code;

	full_command = command->command;
	argc = get_argc(full_command);
	if (argc == 1)
		exit_code = var->exit_status;
	else if (!arg_is_numeric(full_command[1]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit_code = INCORRECT_USAGE;
	}
	else if (argc > 2)
		return (minishell_error_return_failure("exit: too many arguments"));
	else
	{
		exit_code = ft_atoi(full_command[1]);
		exit_code = exit_code % 256;
	}
	free_all_allocated_memory(var);
	printf(BOLDGREEN"Bye bye! See you next time.\n"OFF);
	exit(exit_code);
}
