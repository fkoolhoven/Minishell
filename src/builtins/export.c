/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:20:23 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/04 12:08:13 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// problem: tokenizer splits tokens based on quotes but export actually
// needs the whole string between quotes
// to do: export without any arguments should display all exported variables

char	*get_key(char *command)
{
	char	*key;
	int		i;

	i = 0;
	while (command[i] != '=')
	{
		i++;
	}
	key = ft_substr(command, 0, i);
	return (key);
}

void	copy_value(char *old_value, char *new_value, int key_end)
{
	int	i;
	int	j;

	i = key_end;
	j = 0;
	while (old_value[i])
	{
		if (!char_is_quote(old_value[i]) && !ft_isspace(old_value[i]))
		{
			new_value[j] = old_value[i];
			j++;
		}
		i++;
	}
}


int	calculate_value_strlen(char *value, int key_end)
{
	int	strlen;
	int	i;

	i = key_end;
	strlen = 0;
	while (value[i])
	{
		if (!char_is_quote(value[i]) && !ft_isspace(value[i]))
		{
			strlen++;
		}
		i++;
	}
	return (strlen);
}

char	*get_value(char *command, int key_end)
{
	char	*value;
	int		value_strlen;

	value_strlen = calculate_value_strlen(command, key_end);
	value = ft_calloc(value_strlen + 1, sizeof(char));
	if (value == NULL)
	{
		ft_putendl_fd("malloc error export function", STDERR_FILENO);
		return (NULL);
	}
	copy_value(command, value, key_end);
	return (value);
}

int	export(t_exec_var *var, t_command *command_struct)
{
	char	**command;
	char	*key;
	char	*value;
	int		i;

	command = command_struct->command;
	var = NULL;
	printf("\n\nyay eport, command = %s %s\n\n", command[0], command[1]);

	i = 1;
	while (command[i])
	{
		key = get_key(command[i]);
		printf("key = %s\n", key);
		value = get_value(command[i], ft_strlen(key) + 1);
		printf("value = %s\n", value);
		// create key value pair and add to hashtable;
		i++;
	}
	return (EXIT_SUCCESS);
}
