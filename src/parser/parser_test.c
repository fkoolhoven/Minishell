/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:55:41 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 17:31:52 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ONLY FUNCTIONS FOR TESTING PURPOSES

void	print_redirections(t_redirect *lst)
{
	while (lst)
	{
		printf("type = %i, value = %s\n", lst->type, lst->value);
		lst = lst->next;
	}
}

void	print_string_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		printf("%s ", str_array[i]);
		i++;
	}
}

void	print_command_list(t_command *list)
{
	while (list)
	{
		printf("\nINPUTS:\n");
		print_redirections(list->in);
		printf("\nCOMMAND + ARGS:\n");
		if (list->command)
			print_string_array(list->command);
		printf("\n\nOUTPUTS:\n");
		print_redirections(list->out);
		list = list->next;
	}
}
