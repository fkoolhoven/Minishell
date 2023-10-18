/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd_edit_path.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/18 15:36:52 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/18 15:38:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_find_prevdir(char *new_path, int end)
{
	int	i;

	if (new_path == NULL || end < 0)
		return (0);
	i = end;
	while (new_path[i] != '/' && i >= 0)
		i--;
	return (i);
}

static int	st_rm_last(char *new_path, int i, int len)
{
	while (i < len)
	{
		new_path[i] = '\0';
		i++;
	}
	return (ft_strlen(new_path));
}

static int	st_check_move_end(char *npath, int i, int len)
{
	int	prev_dir;

	if (i + 1 < len && i + 2 == len)
	{
		if (i < 2)
			return (st_rm_last(npath, i, len));
		prev_dir = st_find_prevdir(npath, i - 2);
		cd_move(npath, prev_dir, i + 2, len + 1);
		return (prev_dir);
	}
	return (st_rm_last(npath, i, len));
}

static int	st_check_to_move(char *npath, int i, int len)
{
	int	prev_dir;

	if (i + 2 >= len)
		return (st_check_move_end(npath, i, len));
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
		prev_dir = st_find_prevdir(npath, i - 2);
		cd_move(npath, prev_dir, i + 2, len);
		return (prev_dir);
	}
	else
		return (i + 1);
}

void	cd_edit_newpath(char *new_path, int len)
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
