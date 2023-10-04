/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   valid_path.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 14:29:09 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/04 18:15:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*st_check(char *tmp1, char *cmnd, char **prev_valid)
{
	char	*rtn;

	if (tmp1 == NULL)
		return (NULL);
	if (prev_valid == NULL)
		return (NULL);
	rtn = ft_strjoin(tmp1, cmnd);
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
		tmp1 = ft_strjoin((char const *)paths[i], "/");
		tmp2 = st_check(tmp1, cmnd, &prev_valid);
		if (tmp2 != NULL)
			return (tmp2);
		i++;
	}
	if (prev_valid == NULL)
	{
		if (access((const char *)cmnd, F_OK) == 0)
			return (ft_strdup(cmnd));
		return (prev_valid);
	}
	return (prev_valid);
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
	return (st_find_path(var, cmnd));
}
