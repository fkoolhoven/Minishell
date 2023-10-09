/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:23 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/09 16:41:17 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to do: export without any arguments should display all exported variables

char	*get_key(char *command)
{
	char	*key;
	int		i;

	i = 0;
	while (command[i] != '=')
		i++;
	if (!command[i])
		return (NULL);
	key = ft_substr(command, 0, i);
	if (key == NULL)
		return (malloc_error_return_null("export builtin"));
	return (key);
}

int	calculate_value_strlen(char *value, int key_end)
{
	int	strlen;
	int	i;

	i = key_end;
	strlen = 0;
	while (value[i])
	{
		strlen++;
		i++;
	}
	return (strlen);
}

char	*get_value(char *command, int key_end)
{
	char	*untrimmed_value;
	char	*value;
	int		value_strlen;

	if (command[key_end] == '\0')
		return (NULL);
	value_strlen = calculate_value_strlen(command, key_end);
	untrimmed_value = ft_calloc(value_strlen + 1, sizeof(char));
	if (untrimmed_value == NULL)
		return (malloc_error_return_null("export builtin"));
	ft_strlcpy(untrimmed_value, command + key_end, value_strlen + 1);
	value = ft_strtrim(untrimmed_value, " \f\t\n\r\v");
	free(untrimmed_value);
	if (value == NULL)
		return (malloc_error_return_null("export builtin"));
	return (value);
}

int	print_env_list(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export(t_exec_var *var, t_command *command_struct)
{
	char	**command;
	char	*key;
	char	*value;
	t_hnode	*node;
	int		i;

	command = command_struct->command;
	if (!command[1])
	{
		print_hashtable(var->env);
		return (print_env_list(var->env_str));
	}
	i = 1;
	while (command[i])
	{
		key = get_key(command[i]);
		if (key != NULL)
		{
			value = get_value(command[i], ft_strlen(key) + 1);
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
		i++;
	}
	print_hashtable(var->env);
	return (EXIT_SUCCESS);
}
