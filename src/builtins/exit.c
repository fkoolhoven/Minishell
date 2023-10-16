/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:38:10 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/16 14:32:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all_allocated_memory(t_exec_var *var, t_command *command)
{
	terminate_hashtable(var->env);
	terminate_execvar(var);
	terminate_command_list(&command);
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

static int	get_exit_code(char **full_command, int argc)
{
	int	exit_code;

	if (argc == 1)
		exit_code = EXIT_SUCCESS;
	else
	{
		if (!arg_is_numeric(full_command[1]))
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			exit_code = INCORRECT_USAGE;
		}
		else
		{
			exit_code = ft_atoi(full_command[1]);
			exit_code = exit_code % 256;
		}
	}
	return (exit_code);
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
	if (argc > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		exit_code = get_exit_code(full_command, argc);
	free_all_allocated_memory(var, command);
	printf(BOLDGREEN"Bye bye! See you next time.\n"OFF);
	exit(exit_code);
}
