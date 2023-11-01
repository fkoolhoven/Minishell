/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   valid_path.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:26:18 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 13:55:08 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*st_check(char *tmp1, char *cmnd, char **prev_valid)
{
	char	*rtn;

	if (tmp1 == NULL)
		return (NULL);
	if (prev_valid == NULL)
		return (free(tmp1), NULL);
	rtn = ft_strjoin(tmp1, cmnd);
	if (tmp1 != rtn)
		free(tmp1);
	if (rtn == NULL)
		return (NULL);
	if (access(rtn, X_OK) == 0)
		return (rtn);
	else if (access(rtn, F_OK) == 0)
	{
		if (*prev_valid != NULL)
			free(*prev_valid);
		*prev_valid = rtn;
		return (NULL);
	}
	return (free(rtn), NULL);
}

static void	st_free_in_whileloop(char *prev_valid, char **paths)
{
	if (prev_valid != NULL)
		free(prev_valid);
	if (paths != NULL)
		ft_free_str_array(paths);
}

static char	*st_check_paths(char *cmnd, char **paths)
{
	char	*prev_valid;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	prev_valid = NULL;
	while (paths[i])
	{
		tmp1 = ft_strjoin(paths[i], "/");
		tmp2 = st_check(tmp1, cmnd, &prev_valid);
		if (tmp2 != NULL)
			return (st_free_in_whileloop(prev_valid, paths), tmp2);
		i++;
	}
	if (prev_valid == NULL)
	{
		if (access(cmnd, F_OK) == 0)
			return (ft_free_str_array(paths), ft_strdup(cmnd));
		return (ft_free_str_array(paths), prev_valid);
	}
	return (ft_free_str_array(paths), prev_valid);
}

static char	*st_find_path(t_exec_var *var, t_command *cmnd)
{
	char	**paths;

	if (access((const char *)(cmnd->command[0]), X_OK) == 0)
		return (ft_strdup(cmnd->command[0]));
	paths = ft_split(find_env_value(var->env, "PATH"), ':');
	if (paths == NULL)
	{
		if (access((const char *)(cmnd->command[0]), F_OK) == 0)
			return (ft_strdup(cmnd->command[0]));
		return (NULL);
	}
	if (*paths == NULL)
	{
		if (access((const char *)(cmnd->command[0]), F_OK) == 0)
			return (ft_strdup(cmnd->command[0]));
		return (NULL);
	}
	return (st_check_paths((cmnd->command[0]), paths));
}

char	*find_command_path(t_exec_var *var, t_command *cmnd)
{
	if (cmnd == NULL)
		return (NULL);
	if (cmnd->command == NULL)
		return (NULL);
	if (*(cmnd->command) == NULL)
		return (NULL);
	if (*(cmnd->command)[0] == '\0')
		return (NULL);
	if (ft_strchr((const char *)((cmnd->command)[0]), '/') != NULL)
	{
		if (access((const char *)(cmnd->command[0]), F_OK) == 0)
			return (ft_strdup(cmnd->command[0]));
		return (NULL);
	}
	return (st_find_path(var, cmnd));
}
