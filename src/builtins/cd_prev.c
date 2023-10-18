/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_prev.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:37:15 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/18 15:38:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*st_give_changing_path(t_exec_var *var)
{
	char	*tmp_path;
	char	*new_path;

	tmp_path = ft_strjoin(var->cur_path, "/..");
	if (tmp_path == NULL)
		return (NULL);
	new_path = cd_strtrim(tmp_path, "/");
	if (new_path == NULL)
		return (free(tmp_path), NULL);
	cd_edit_newpath(new_path, ft_strlen(new_path));
	return (free(tmp_path), new_path);
}

static char	*st_give_error_path(t_exec_var *var)
{
	char	*rtn;

	rtn = ft_strjoin(var->cur_path, "/..");
	return (rtn);
}

int	cd_prev_dir(t_exec_var *var)
{
	int		check;
	char	*new_path;
	char	*err_path;

	check = 0;
	new_path = st_give_changing_path(var);
	check = chdir(new_path);
	if (check < 0 && new_path[0] != '\0')
	{
		err_path = st_give_error_path(var);
		cd_change_curpath(var, new_path, err_path, EXIT_FAILURE);
		free(err_path);
		check = cd_change_env(var, new_path, EXIT_FAILURE);
		return (free(new_path), check);
	}
	if (check < 0)
		return (EXIT_SUCCESS);
	cd_change_curpath(var, new_path, NULL, EXIT_SUCCESS);
	check = cd_change_env(var, new_path, EXIT_SUCCESS);
	return (free(new_path), check);
}
