/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:37:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/13 16:47:41 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_give_args_count(char **command)
{
	int	argc;

	if (command == NULL)
		return (-1);
	argc = 0;
	while (command[argc])
		argc++;
	return (argc);
}

static int	st_change_env(t_exec_var *var, char *new_path)
{
	t_hnode	*pwd;
	t_hnode	*oldpwd;

	if (new_path == NULL)
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
		(pwd->value) = ft_strdup(new_path);
	}
	return (EXIT_SUCCESS);
}

static int	st_put_error(char *message, char *key)
{
	if (message != NULL)
		ft_putstr_fd(message, 2);
	if (key != NULL)
	{
		ft_putstr_fd(key, 2);
		ft_putstr_fd("not set\n", 2);
	}
	return (EXIT_FAILURE);
}

static int	st_go_key(t_exec_var *var, char *key)
{
	int		check;
	char	*path;

	if (var == NULL)
		return (EXIT_FAILURE);
	path = find_env_value(var->env, key);
	if (path == NULL)
		return (st_put_error(NULL, key));
	check = chdir(path);
	if (check < 0)
		return (EXIT_FAILURE);
	ft_bzero(var->cur_path, PATH_MAX);
	ft_strlcpy(var->cur_path, path, PATH_MAX);
	return (st_change_env(var, path));
}

static int	st_is_absolute_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	st_check_change_dirs(t_exec_var *var, char *path)
{
	if (ft_strncmp(path, "-", 2) == 0)
	{
		printf("%s\n", find_env_value(var->env, "OLDPWD"));
		return (st_go_key(var, "OLDPWD"));
	}
	if (ft_strncmp(path, "--", 3) == 0)
		return (st_go_key(var, "HOME"));
	if (st_is_absolute_path(path) == EXIT_SUCCESS)
		return (...);
	return (...);
}

int	bltin_cd(t_exec_var *var, t_command *cmnd)
{
	int	argc;

	if (var == NULL || cmnd == NULL)
		return (EXIT_FAILURE);
	argc = st_give_args_count(cmnd->command);
	if (argc <= 0)
		return (EXIT_FAILURE);
	if (argc > 2)
	{
		ft_putstr_fd((cmnd->command)[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (argc == 1)
		return (st_go_key(var, "HOME"));
	return (st_check_change_dirs(var, (cmnd->commands)[1]));
}
