/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_terminate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:41:43 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 19:17:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate_redirect_list_error(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		free(redirect);
		redirect = temp;
	}
}

void	terminate_redirect_list(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		if (redirect->value)
			free(redirect->value);
		free(redirect);
		redirect = temp;
	}
}

void	terminate_command_list_error(t_command **list_start)
{
	t_command	*command;
	t_command	*temp;

	command = *list_start;
	printf("WANT TO TERMINATE COMMAND command = %p\n", command);
	while (command)
	{
		printf("TERMINATING COMMAND\n");
		temp = command->next;
		terminate_redirect_list_error(command->in);
		// ft_free_str_array(command->command);
		free(command->command);
		terminate_redirect_list_error(command->out);
		free(command);
		command = temp;
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
		terminate_redirect_list(command->in);
		ft_free_str_array(command->command);
		terminate_redirect_list(command->out);
		free(command);
		command = temp;
	}
}

void	*parser_terminate_error(t_list **list_start, t_parser_var *var)
{
	if (var->in)
		terminate_redirect_list_error(var->in);
	if (var->out)
		terminate_redirect_list_error(var->out);
	terminate_token_list_error(list_start);
	terminate_command_list_error(&var->command_list);
	free(var->command);
	free(var);
	return (NULL);
}
