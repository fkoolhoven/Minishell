/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:42:44 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/18 15:39:08 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	st_put_partial_str(char *str, int start, int end, int size)
{
	int	check;

	if (size < 0 || start < 0 || end < start)
		return (-1);
	if (start + end > size || str == NULL)
		return (-1);
	check = write(STDIN_FILENO, str + start, end - start);
	if (check < 0)
		return (-1);
	return (0);
}

static int	st_with_status(t_exec_var *var, char *arg, int start, int end)
{
	int	check;

	check = st_put_partial_str(arg, start, end, ft_strlen(arg));
	if (check < 0)
		return (check);
	check = printf("%i", var->exit_status);
	if (check < 0)
		return (check);
	return (0);
}

static int	st_display_special_arg(t_exec_var *var, char *arg)
{
	int	i;
	int	start;

	if (arg == NULL)
		return (-1);
	i = 0;
	start = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			if (st_with_status(var, arg, start, i - 1) < 0)
				return (-1);
			start = i + 1;
		}
		i++;
		if (arg[i] == '\0')
		{
			if (st_put_partial_str(arg, start, i, ft_strlen(arg)) < 0)
				return (-1);
		}
	}
	return (0);
}

static int	st_display_args(t_exec_var *var, t_command *command, int start)
{
	int		i;
	int		check;
	char	**cmnd;

	i = start;
	cmnd = command->command;
	while (cmnd[i])
	{
		if (ft_strnstr(cmnd[i], "$?", ft_strlen(cmnd[i])) != NULL)
			check = st_display_special_arg(var, cmnd[i]);
		else
			check = printf("%s", cmnd[i]);
		if (check < 0)
			return (EXIT_FAILURE);
		if (cmnd[i + 1] != NULL)
		{
			check = printf(" ");
			if (check < 0)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	bltin_echo(t_exec_var *var, t_command *command)
{
	int	check;

	rl_on_new_line();
	if (var == NULL || command == NULL)
		return (EXIT_FAILURE);
	if (command->command == NULL)
		return (EXIT_FAILURE);
	if ((command->command)[1] == NULL)
	{
		check = printf("\n");
		if (check < 0)
			return (EXIT_FAILURE);
		rl_on_new_line();
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp((command->command)[1], "-n", 3) == 0)
		return (st_display_args(var, command, 2));
	check = st_display_args(var, command, 1);
	if (check != EXIT_SUCCESS)
		return (check);
	check = printf("\n");
	if (check < 0)
		return (EXIT_FAILURE);
	rl_on_new_line();
	return (EXIT_SUCCESS);
}
