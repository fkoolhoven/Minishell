/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_curpath.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:36:35 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/20 11:17:18 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp_path = cd_strtrim(new_path, "/");
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

	tmp_path = ft_strjoin(var->cur_path, "/");
	if (tmp_path == NULL)
		return (NULL);
	new_path = ft_strjoin(tmp_path, path);
	if (new_path != tmp_path)
		free(tmp_path);
	if (new_path == NULL)
		return (NULL);
	tmp_path = cd_strtrim(new_path, "/");
	free(new_path);
	return (tmp_path);
}

int	cd_change_with_path(t_exec_var *var, char *path)
{
	int		check;
	char	*err_path;
	char	*new_path;

	if (var == NULL || path == NULL)
		return (EXIT_FAILURE);
	new_path = st_give_changing_path(var, path);
	printf("new_path: %s\n", new_path);
	if (new_path == NULL)
		return (EXIT_FAILURE);
	check = chdir(new_path);
	if (check < 0 && new_path != NULL && *new_path != '\0')
	{
		err_path = st_give_error_path(var, path);
		cd_ch_curpath(var, new_path, err_path, EXIT_FAILURE);
		free(err_path);
		check = cd_change_env(var, new_path, EXIT_FAILURE);
		return (free(new_path), check);
	}
	if (check < 0)
		return (free(new_path), EXIT_SUCCESS);
	cd_ch_curpath(var, new_path, NULL, EXIT_SUCCESS);
	check = cd_change_env(var, new_path, EXIT_SUCCESS);
	return (free(new_path), check);
}
