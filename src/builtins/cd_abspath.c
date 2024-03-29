/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_abspath.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:36:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 14:22:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*st_give_changing_path(char *path)
{
	char	*tmp_path;

	tmp_path = cd_strtrim(path, "/");
	if (tmp_path == NULL)
		return (NULL);
	cd_edit_newpath(tmp_path, ft_strlen(tmp_path));
	return (tmp_path);
}

int	cd_absolute_path(t_exec_var *var, char *path)
{
	int		check;
	char	*tmp_path;

	if (var == NULL || path == NULL)
		return (EXIT_FAILURE);
	tmp_path = st_give_changing_path(path);
	if (tmp_path == NULL)
		return (cd_put_error("Error: trimming path failed\n", NULL, path));
	check = chdir(tmp_path);
	if (check < 0)
	{
		check = cd_put_error(NULL, NULL, tmp_path);
		return (free(tmp_path), check);
	}
	cd_ch_curpath(var, tmp_path, NULL, EXIT_SUCCESS);
	check = cd_change_env(var, tmp_path, EXIT_SUCCESS);
	return (free(tmp_path), check);
}
