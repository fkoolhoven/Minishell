/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:23 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/16 16:46:55 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *command)
{
	char	*key;
	int		i;

	i = 0;
	while (command[i] && command[i] != '=')
		i++;
	if (!command[i])
		return (NULL);
	key = ft_substr(command, 0, i);
	if (key == NULL)
		return (malloc_error_return_null("export builtin"));
	return (key);
}

static void	print_env_list(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	attempt_to_export(t_exec_var *var, char *input)
{
	t_hnode	*node;
	char	*key;
	char	*value;

	key = get_key(input);
	if (key != NULL)
	{
		value = get_value(input, ft_strlen(key) + 1);
		node = find_env_valuenode(var->env, key);
		if (node)
		{
			if (node->value)
				free(node->value);
			node->value = value;
		}
		else
			add_pair(var->env, key, value);
	}
}

int	bltin_export(t_exec_var *var, t_command *command_struct)
{
	char	**command;
	int		i;

	command = command_struct->command;
	i = 1;
	if (!command[i])
	{
		print_env_list(var->env_str);
		return (EXIT_FAILURE);
	}
	while (command[i])
	{
		attempt_to_export(var, command[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
