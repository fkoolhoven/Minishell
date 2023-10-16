/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_utils.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/16 11:22:33 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/16 16:57:04 by jhendrik      ########   odam.nl         */
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

int	cd_change_env(t_exec_var *var, char *new_path)
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
		(pwd->value) = ft_strdup(new_path);
	}
	if (ft_strncmp(var->cur_path, new_path, ft_strlen(new_path) + 1) != 0)
	{
		ft_bzero(var->cur_path, PATH_MAX);
		ft_strlcpy(var->cur_path, new_path, PATH_MAX);
	}
	return (EXIT_SUCCESS);
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

void	cd_move(char *new_path, int start, int end, int size)
{
	int	i;

	if (new_path != NULL && start <= end && end < size)
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

int	cd_find_prevdir(char *new_path, int end)
{
	int	i;

	if (new_path == NULL || end < 0)
		return (0);
	i = end;
	while (new_path[i] != '/' && i >= 0)
		i--;
	return (i);
}
