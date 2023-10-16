/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:37:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/16 13:19:43 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_go_key(t_exec_var *var, char *key)
{
	int		check;
	char	*path;

	if (var == NULL)
		return (EXIT_FAILURE);
	path = find_env_value(var->env, key);
	if (path == NULL)
		return (cd_put_error(NULL, key, path));
	check = chdir(path);
	if (check < 0)
		return (cd_put_error(NULL, NULL, path));
	return (cd_change_env(var, path));
}

static int	st_absolute_path(t_exec_var *var, char *path)
{
	int	check;

	if (var == NULL || path == NULL)
		return (EXIT_FAILURE);
	check = chdir(path);
	if (check < 0)
		return (cd_put_error(NULL, NULL, path));
	return (cd_change_env(var, path));
}

static int	st_check_change_dirs(t_exec_var *var, char *path)
{
	char	*tmp;

	if (ft_strncmp(path, "-", 2) == 0)
	{
		tmp = find_env_value(var->env, "OLDPWD");
		if (tmp != NULL)
			printf("%s\n", find_env_value(var->env, "OLDPWD"));
		return (st_go_key(var, "OLDPWD"));
	}
	if (ft_strncmp(path, "--", 3) == 0)
		return (st_go_key(var, "HOME"));
	if (ft_strnstr(path, "./", ft_strlen(path) + 1) == NULL)
	{
		if (ft_strnstr(path, "..", ft_strlen(path) + 1) == NULL)
		{
			if (ft_strncmp(path, ".", ft_strlen(path) + 1) != 0)
				return (st_absolute_path(var, path));
		}
	}
	return (cd_change_with_path(var, path));
}

int	bltin_cd(t_exec_var *var, t_command *cmnd)
{
	int	argc;

	if (var == NULL || cmnd == NULL)
		return (EXIT_FAILURE);
	argc = cd_give_args_count(cmnd->command);
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
	return (st_check_change_dirs(var, (cmnd->command)[1]));
}
