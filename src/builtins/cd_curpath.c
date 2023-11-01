/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_curpath.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:36:35 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 11:50:51 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*st_give_changing_path(t_exec_var *var, char *path)
{
	char	*tmp_path;
	char	*new_path;

	if (var == NULL || path == NULL)
		return (NULL);
	tmp_path = ft_strjoin(var->cur_path, "/"); // good
	if (tmp_path == NULL)
		return (NULL);
	new_path = ft_strjoin(tmp_path, path); // good
	if (new_path != tmp_path && tmp_path != var->cur_path)
		free(tmp_path);
	if (new_path == NULL)
		return (NULL);
	tmp_path = cd_strtrim(new_path, "/"); // good
	free(new_path);
	if (tmp_path == NULL)
		return (NULL);
	cd_edit_newpath(tmp_path, ft_strlen(tmp_path));
	return (tmp_path);
}

static char	*st_give_error_path(t_exec_var *var, char *path)
{
	char	*tmp_path;
	char	*new_path;

	if (var == NULL || path == NULL)
		return (NULL);
	tmp_path = ft_strjoin(var->cur_path, "/"); // good
	if (tmp_path == NULL)
		return (NULL);
	new_path = ft_strjoin(tmp_path, path); // good
	if (new_path != tmp_path && tmp_path != var->cur_path)
		free(tmp_path);
	if (new_path == NULL)
		return (NULL);
	tmp_path = cd_strtrim(new_path, "/"); // good
	free(new_path);
	return (tmp_path);
}

static bool	st_is_relative(char *path)
{
	size_t	i;

	if (path == NULL)
		return (false);
	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
			i++;
		else if (path[i] == '/')
			i++;
		else
			return (false);
	}
	return (true);
}

int	cd_change_with_path(t_exec_var *var, char *path)
{
	int		check;
	char	*err_path;
	char	*new_path;

	if (var == NULL || path == NULL)
		return (EXIT_FAILURE);
	new_path = st_give_changing_path(var, path); // good
	if (new_path == NULL)
		return (cd_put_error("Error: strjoin or strtrim failed\n", NULL, path));
	check = chdir(new_path);
	if (check < 0 && new_path != NULL && *new_path != '\0' && st_is_relative(path))
	{
		err_path = st_give_error_path(var, path); // good
		if (err_path != NULL)
		{
			cd_ch_curpath(var, new_path, err_path, EXIT_FAILURE);
			free(err_path);
			check = cd_change_env(var, new_path, EXIT_FAILURE);
		}
		else 
			check = cd_put_error("Error: strjoin or strtrim failed\n", NULL, path);
		return (free(new_path), check);
	}
	else if (check < 0 && new_path != NULL && *new_path != '\0')
	{
		check = cd_put_error(NULL, NULL, new_path);
		return (free(new_path), check);
	}
	if (check < 0)
		return (free(new_path), EXIT_SUCCESS);
	cd_ch_curpath(var, new_path, NULL, EXIT_SUCCESS);
	check = cd_change_env(var, new_path, EXIT_SUCCESS);
	return (free(new_path), check);
}
