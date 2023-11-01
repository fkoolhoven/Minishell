/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   env_change_env.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 12:32:15 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/11/01 13:09:13 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_update_oldpwd(t_hnode *pwd, t_hnode *oldpwd)
{
	if (oldpwd != NULL && pwd != NULL)
	{
		if (oldpwd->value != NULL)
			free(oldpwd->value);
		(oldpwd->value) = (pwd->value);
	}
}

static char	*st_give_newpwd(int status, char *new_path, t_exec_var *var)
{
	char	*tmp;

	if (status == EXIT_SUCCESS)
		tmp = ft_strdup(new_path);
	else
		tmp = ft_strdup(var->cur_path);
	return (tmp);
}

int	cd_change_env(t_exec_var *var, char *new_path, int status)
{
	t_hnode	*pwd;
	t_hnode	*oldpwd;
	char	*tmp;

	if (new_path == NULL || var == NULL)
		return (EXIT_FAILURE);
	pwd = find_env_valuenode(var->env, "PWD");
	oldpwd = find_env_valuenode(var->env, "OLDPWD");
	st_update_oldpwd(pwd, oldpwd);
	if (pwd != NULL)
	{
		if (pwd->value != NULL && oldpwd == NULL)
			free(pwd->value);
		tmp = st_give_newpwd(status, new_path, var);
		if (tmp != NULL)
			(pwd->value) = tmp;
		else
		{
			ft_putstr_fd("Error: dup failed, PWD not changed\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
