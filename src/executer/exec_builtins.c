/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_builtins.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 09:57:46 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/11 12:16:49 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*st_give_cmnd_nopath(t_command *command)
{
	char	**no_path_cmnd;
	char	*return_str;
	int		i;

	if (command == NULL)
		return (NULL);
	if (command->command == NULL)
		return (NULL);
	no_path_cmnd = ft_split((command->command)[0], '/');
	if (no_path_cmnd == NULL)
		return ((command->command)[0]);
	i = 0;
	while (no_path_cmnd[i])
	{
		if (no_path_cmnd[i + 1] == NULL)
		{
			return_str = ft_strdup((const char *)no_path_cmnd[i]);
			return (ft_free_str_array(no_path_cmnd), return_str);
		}
		i++;
	}
	ft_free_str_array(no_path_cmnd);
	return (NULL);
}

int	check_if_builtin(t_exec_var *var, t_command *command)
{
	const char	*builtins[] = {
		"cd", "echo",
		"env", "exit",
		"export", "pwd",
		"unset", NULL};
	char		*no_path_cmnd;
	int			i;

	if (var == NULL || command == NULL)
		return (-2);
	no_path_cmnd = st_give_cmnd_nopath(command);
	if (no_path_cmnd == NULL)
		return (-2);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(builtins[i], no_path_cmnd, ft_strlen(no_path_cmnd)) == 0)
			return (free(no_path_cmnd), i);
		i++;
	}
	return (free(no_path_cmnd), -1);
}

int	execute_builtin(t_exec_var *var, t_command *cmnd, int bltin)
{
	t_f_bltin	jmptbl[7];

	jmptbl[0] = &bltin_cd;
	jmptbl[1] = &bltin_echo;
	jmptbl[2] = &bltin_env;
	jmptbl[3] = &bltin_exit;
	jmptbl[4] = &bltin_export;
	jmptbl[5] = &bltin_pwd;
	jmptbl[6] = &bltin_unset;
	if (bltin >= 0 && bltin <= 6)
		return (jmptbl[bltin](var, cmnd));
	else
		return (jmptbl[(bltin % 7)](var, cmnd));
}
