/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_builtins.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 09:57:46 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/27 15:52:48 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_if_builtin(t_exec_var *var, t_command *command)
{
	const char	*builtins[] = {
		"cd", "echo",
		"env", "exit",
		"export", "pwd",
		"unset", NULL};
	int			i;
	char		*cmnd;

	if (var == NULL || command == NULL)
		return (-2);
	if (command->command == NULL)
		return (-2);
	if ((command->command)[0] == NULL)
		return (-2);
	cmnd = (command->command)[0];
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(builtins[i], cmnd, ft_strlen(cmnd) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	execute_builtin(t_exec_var *var, t_command *cmnd, int bltin)
{
	int			status;
	t_f_bltin	jmptbl[7];

	jmptbl[0] = &bltin_cd;
	jmptbl[1] = &bltin_echo;
	jmptbl[2] = &bltin_env;
	jmptbl[3] = &bltin_exit;
	jmptbl[4] = &bltin_export;
	jmptbl[5] = &bltin_pwd;
	jmptbl[6] = &bltin_unset;
	if (bltin >= 0 && bltin <= 6)
		status = jmptbl[bltin](var, cmnd);
	else
		status = jmptbl[(bltin % 7)](var, cmnd);
	return (status);
}
