/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_terminate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:41:43 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/25 15:24:51 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	terminate_redirect_list_error(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		free(redirect);
		redirect = temp;
	}
}

static void	terminate_redirect_list(t_redirect *redirect)
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

static void	terminate_command_list_error(t_command **list_start)
{
	t_command	*command;
	t_command	*temp;

	command = *list_start;
	while (command)
	{
		temp = command->next;
		terminate_redirect_list_error(command->in);
		terminate_redirect_list_error(command->out);
		free(command->command);
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
		temp = command->next;
		terminate_redirect_list(command->in);
		terminate_redirect_list(command->out);
		ft_free_str_array(command->command);
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
