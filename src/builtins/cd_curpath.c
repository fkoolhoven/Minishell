/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_curpath.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/16 11:35:52 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/16 13:21:01 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_rm_last(char *new_path, int i, int len)
{
	while (i < len)
	{
		new_path[i] = '\0';
		i++;
	}
	return (ft_strlen(new_path));
}

static int	st_check_to_move(char *npath, int i, int len)
{
	int	prev_dir;

	if (i + 2 >= len)
		return (st_rm_last(npath, i, len));
	if (npath[i + 1] == '/' || npath[i + 1] == '\0')
	{
		cd_move(npath, i, i + 2, len);
		if (i > 0)
			return (i - 1);
		else
			return (i);
	}
	if (npath[i + 1] == '.' && (npath[i + 2] == '/' || npath[i + 2] == '\0'))
	{
		if (i < 2)
			return (st_rm_last(npath, i, len));
		prev_dir = cd_find_prevdir(npath, i - 2);
		cd_move(npath, prev_dir, i + 2, len);
		return (prev_dir);
	}
	else
		return (i + 1);
}

static void	st_edit_newpath(char *new_path, int len)
{
	int	i;

	if (new_path != NULL)
	{
		i = 0;
		while (new_path[i])
		{
			if (i > 0)
			{
				if (new_path[i] == '.' && new_path[i - 1] == '/')
					i = st_check_to_move(new_path, i, len);
				else
					i++;
			}
			else if (new_path[i] == '.')
				i = st_check_to_move(new_path, i, len);
			else
				i++;
		}
	}
}

static char	*st_give_changing_path(t_exec_var *var, char *path)
{
	char	*tmp_path;
	char	*new_path;

	tmp_path = ft_strjoin(var->cur_path, "/");
	if (tmp_path == NULL)
		return (NULL);
	new_path = ft_strjoin(tmp_path, path);
	if (new_path != tmp_path)
		free(tmp_path);
	if (new_path == NULL)
		return (NULL);
	st_edit_newpath(new_path, ft_strlen(new_path));
	tmp_path = ft_strtrim(new_path, "/");
	free(new_path);
	if (tmp_path == NULL)
	{
		cd_put_error("No path left\n", NULL, path);
		return (NULL);
	}
	return (tmp_path);
}

int	cd_change_with_path(t_exec_var *var, char *path)
{
	int		check;
	int		len;
	char	*new_path;

	if (var == NULL || path == NULL)
		return (EXIT_FAILURE);
	new_path = st_give_changing_path(var, path);
	if (new_path == NULL)
		return (EXIT_FAILURE);
	check = chdir(new_path);
	if (check < 0)
	{
		len = ft_strlen(var->cur_path);
		if (len + 3 < PATH_MAX)
		{
			(var->cur_path)[len + 1] = '/';
			(var->cur_path)[len + 2] = '.';
			(var->cur_path)[len + 3] = '.';
		}
		cd_put_error(NULL, NULL, new_path);
		return (free(new_path), cd_change_env(var, (var->cur_path)));
	}
	check = cd_change_env(var, new_path);
	return (free(new_path), check);
}
