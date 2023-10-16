/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:37:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/16 17:19:18 by jhendrik      ########   odam.nl         */
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
	int		check;
	char	*tmp_path;

	if (var == NULL || path == NULL)
		return (EXIT_FAILURE);
	tmp_path = cd_strtrim(path, "/");
	if (tmp_path == NULL)
		return(EXIT_FAILURE);
	check = chdir(tmp_path);
	if (check < 0)
	{
		check = cd_put_error(NULL, NULL, tmp_path);
		return (free(tmp_path), check);
	}
	check = cd_change_env(var, tmp_path);
	return (free(tmp_path), check);
}

static int	st_prev_dir(t_exec_var *var)
{
	int		prev_dir;
	int		check;
	int		size;
	char	new_path[ft_strlen(var->cur_path) + 1];

	size = ft_strlen(var->cur_path) + 1;
	check = 0;
	prev_dir = cd_find_prevdir(var->cur_path, size - 2);
	while ((var->cur_path)[check] != '\0')
	{
		if (check < prev_dir)
			new_path[check] = (var->cur_path)[check];
		else 
			new_path[check] = '\0';
		check++;
	}
	check = chdir(new_path);
	if (check < 0 && new_path[0] != '\0')
	{
		if (size + 2 < PATH_MAX)
		{
			(var->cur_path)[size] = '/';
			(var->cur_path)[size + 1] = '.';
			(var->cur_path)[size + 2] = '.';
		}
		cd_put_error(NULL, NULL, new_path);
		return (cd_change_env(var, (var->cur_path)));
	}
	if (check < 0)
		return (EXIT_SUCCESS);
	return (cd_change_env(var, new_path));
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
	if (ft_strncmp(path, ".", 2) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(path, "..", 3) == 0)
		return (st_prev_dir(var));
/*	if (ft_strnstr(path, "./", ft_strlen(path) + 1) == NULL)
	{
		if (ft_strnstr(path, "..", ft_strlen(path) + 1) == NULL)
		{
			if (path[0] == '/')
				return (st_absolute_path(var, path));
		}
	} */ 
	if (path[0] == '/')
		return (st_absolute_path(var, path));
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
