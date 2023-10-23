/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:45:09 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/23 16:02:56 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_value_strlen(char *value, int key_end)
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
	char	*value;
	int		value_strlen;

	if (command[key_end] == '\0')
		return (NULL);
	value_strlen = calculate_value_strlen(command, key_end);
	value = ft_calloc(value_strlen + 1, sizeof(char));
	if (value == NULL)
		return (malloc_error_return_null("export builtin"));
	ft_strlcpy(value, command + key_end, value_strlen + 1);
	if (value == NULL)
		return (malloc_error_return_null("export builtin"));
	return (value);
}
