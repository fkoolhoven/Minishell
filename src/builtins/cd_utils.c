/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_utils.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:38:23 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 14:29:45 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_give_args_count(char **command)
{
	int	argc;

	if (command == NULL)
		return (-1);
	argc = 0;
	while (command[argc])
		argc++;
	return (argc);
}

int	cd_put_error(char *message, char *key, char *path)
{
	if (message != NULL)
		ft_putstr_fd(message, 2);
	else if (key != NULL)
	{
		ft_putstr_fd(key, 2);
		ft_putstr_fd("not set\n", 2);
	}
	else
		perror(path);
	return (EXIT_FAILURE);
}

void	cd_ch_curpath(t_exec_var *var, char *npath, char *epath, int status)
{
	char	check_str[PATH_MAX];

	if (npath != NULL && var != NULL)
	{
		if (status != EXIT_SUCCESS && epath != NULL)
		{
			if (getcwd(check_str, PATH_MAX) == NULL)
			{
				perror(npath);
				ft_bzero(var->cur_path, PATH_MAX);
				ft_strlcpy(var->cur_path, epath, PATH_MAX);
			}
			else
				cd_put_error(NULL, NULL, npath);
		}
		else if (epath == NULL)
		{
			ft_bzero(var->cur_path, PATH_MAX);
			ft_strlcpy(var->cur_path, npath, PATH_MAX);
		}
	}
}

void	cd_move(char *new_path, int start, int end, int size)
{
	int	i;

	if (new_path != NULL && start <= end && end <= size)
	{
		if (start >= 0 && end >= 0)
		{
			i = 0;
			while (new_path[i + end])
			{
				new_path[i + start] = new_path[i + end];
				i++;
			}
			while (i + start < size)
			{
				new_path[i + start] = '\0';
				i++;
			}
		}
	}
}
