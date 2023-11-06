/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:42:44 by jhendrik          #+#    #+#             */
/*   Updated: 2023/11/06 15:49:14 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_put_partial_str(char *str, int start, int end, int size)
{
	int	check;

	if (start == 0 && end < 0)
		return (0);
	if (size < 0 || start < 0 || end < start)
		return (-1);
	if (end > size || str == NULL)
		return (-1);
	check = write(STDOUT_FILENO, str + start, end - start);
	if (check < 0)
		return (-1);
	return (0);
}

// static int	st_with_status(t_exec_var *var, char *arg, int start, int end)
// {
// 	int		check;
// 	char	*nb;

// 	if (var == NULL)
// 		return (-1);
// 	check = st_put_partial_str(arg, start, end + 1, ft_strlen(arg));
// 	if (check < 0)
// 		return (check);
// 	nb = ft_itoa(var->exit_status);
// 	if (nb == NULL)
// 	{
// 		write(STDERR_FILENO, "ft_itoa failed\n", 15);
// 		return (-1);
// 	}
// 	check = write(STDOUT_FILENO, nb, ft_strlen(nb));
// 	if (check < 0)
// 		return (free(nb), check);
// 	return (free(nb), 0);
// }

static int	st_display_special_arg(char *arg)
{
	int	i;
	int	start;

	if (arg == NULL)
		return (-1);
	i = 0;
	start = 0;
	while (arg[i])
	{
		// if (arg[i] == '$' && arg[i + 1] == '?')
		// {
		// 	if (st_with_status(var, arg, start, i - 1) < 0)
		// 		return (-1);
		// 	start = i + 2;
		// 	i++;
		// }
		i++;
		if (arg[i] == '\0')
		{
			if (st_put_partial_str(arg, start, i, ft_strlen(arg)) < 0)
				return (-1);
		}
	}
	return (0);
}

static int	st_display_args(t_command *command, int start)
{
	int		i;
	int		check;
	char	**cmnd;

	i = start;
	cmnd = command->command;
	while (cmnd[i])
	{
		if (ft_strnstr(cmnd[i], "$?", ft_strlen(cmnd[i]) + 1) != NULL)
			check = st_display_special_arg(cmnd[i]);
		else
			check = write(STDOUT_FILENO, cmnd[i], ft_strlen(cmnd[i]));
		if (check < 0)
			return (EXIT_FAILURE);
		if (cmnd[i + 1] != NULL)
		{
			check = write(STDOUT_FILENO, " ", 1);
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
		check = write(STDOUT_FILENO, "\n", 1);
		if (check < 0)
			return (EXIT_FAILURE);
		rl_on_new_line();
		return (EXIT_SUCCESS);
	}
	if (echo_optioncheck((command->command)[1]))
		return (st_display_args(command, 2));
	check = st_display_args(command, 1);
	if (check != EXIT_SUCCESS)
		return (check);
	check = write(STDOUT_FILENO, "\n", 1);
	if (check < 0)
		return (EXIT_FAILURE);
	rl_on_new_line();
	return (EXIT_SUCCESS);
}
