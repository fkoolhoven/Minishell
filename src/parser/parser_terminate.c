/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_terminate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:41:43 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 15:31:23 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_redirect
// {
// 	enum e_type			type;
// 	char				*value;
// 	struct s_redirect	*next;
// }	t_redirect;

// typedef struct s_command
// {
// 	char				**command;
// 	struct s_redirect	*out;
// 	struct s_redirect	*in;
// 	struct s_command	*next;
// }	t_command;

void	terminate_redirect_list(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		free(redirect->value);
		free(redirect);
		redirect = temp;
	}
}

void	terminate_command_list(t_command **list_start)
{
	t_command	*command;
	t_command	*temp;

	command = *list_start;
	while (command)
	{
		printf("TERMINATING COMMAND\n");
		temp = command->next;
		free(command->in);
		ft_free_str_array(command->command);
		free(command->out);
		free(command);
		command = temp;
	}
}
