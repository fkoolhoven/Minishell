/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_utils.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:38:23 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/18 15:39:08 by jhendrik      ########   odam.nl         */
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

void	cd_change_curpath(t_exec_var *var, char *npath, char *epath, int status)
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
		else
		{
			ft_bzero(var->cur_path, PATH_MAX);
			ft_strlcpy(var->cur_path, npath, PATH_MAX);
		}
	}
}

int	cd_change_env(t_exec_var *var, char *new_path, int status)
{
	t_hnode	*pwd;
	t_hnode	*oldpwd;

	if (new_path == NULL || var == NULL)
		return (EXIT_FAILURE);
	pwd = find_env_valuenode(var->env, "PWD");
	oldpwd = find_env_valuenode(var->env, "OLDPWD");
	if (oldpwd != NULL && pwd != NULL)
	{
		if (oldpwd->value != NULL)
			free(oldpwd->value);
		(oldpwd->value) = (pwd->value);
	}
	if (pwd != NULL)
	{
		if (pwd->value != NULL && oldpwd == NULL)
			free(pwd->value);
		if (status == EXIT_SUCCESS)
			(pwd->value) = ft_strdup(new_path);
		else
			(pwd->value) = ft_strdup(var->cur_path);
	}
	return (EXIT_SUCCESS);
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
