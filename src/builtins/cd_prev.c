/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_prev.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:37:15 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 11:54:50 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*st_give_changing_path(t_exec_var *var)
{
	char	*tmp_path;
	char	*new_path;

	if (var == NULL)
		return (NULL);
	tmp_path = ft_strjoin(var->cur_path, "/.."); // good
	if (tmp_path == NULL)
		return (NULL);
	new_path = cd_strtrim(tmp_path, "/");
	if (new_path == NULL && tmp_path != var->cur_path)
		return (free(tmp_path), NULL);
	else if (new_path == NULL)
		return (NULL);
	cd_edit_newpath(new_path, ft_strlen(new_path));
	return (free(tmp_path), new_path);
}

static char	*st_give_error_path(t_exec_var *var)
{
	char	*rtn;

	rtn = ft_strjoin(var->cur_path, "/.."); // good
	return (rtn);
}

int	cd_prev_dir(t_exec_var *var)
{
	int		check;
	char	*new_path;
	char	*err_path;

	check = 0;
	new_path = st_give_changing_path(var); // good
	if (new_path == NULL)
		return (cd_put_error("Error: strjoin or strtrim failed\n", NULL, NULL));
	check = chdir(new_path);
	if (check < 0 && new_path[0] != '\0')
	{
		err_path = st_give_error_path(var); // good
		if (err_path != NULL)
		{
			cd_ch_curpath(var, new_path, err_path, EXIT_FAILURE);
			free(err_path);
			check = cd_change_env(var, new_path, EXIT_FAILURE);
		}
		else
			check = cd_put_error("Error: strjoin failed\n", NULL, NULL);
		return (free(new_path), check);
	}
	if (check < 0)
		return (EXIT_SUCCESS);
	cd_ch_curpath(var, new_path, NULL, EXIT_SUCCESS);
	check = cd_change_env(var, new_path, EXIT_SUCCESS);
	return (free(new_path), check);
}
