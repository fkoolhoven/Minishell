/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:59:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/29 11:58:38 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This file is the basis for the parsing process

// Adds new command struct (node) to command list.
void	add_command_to_list(t_parser_var *var)
{
	t_command	*new_command;

	if (!var->command_list)
	{
		var->command_list = lstnew_command(var->command, var->in, var->out);
		if (var->command_list == NULL)
		{
			printf("Error allocating for command_list\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_command = lstnew_command(var->command, var->in, var->out);
		if (new_command == NULL)
		{
			printf("Error allocating for new_command\n");
			exit(EXIT_FAILURE);
		}
		lstadd_back_command(&var->command_list, new_command);
	}
}

// Resets the variables needed for creating another command struct.
void	reset_vars(t_list **tokens, t_token **token, t_parser_var *var)
{
	var->in = NULL;
	var->out = NULL;
	var->command = NULL;
	var->amount_of_words = 0;
	*token = (t_token *)(*tokens)->content;
}

// Initializes the vars struct and its contents.
t_parser_var	*init_parser_vars(void)
{
	t_parser_var	*var;

	var = malloc(sizeof(t_parser_var));
	if (var == NULL)
	{
		ft_putendl_fd("minishell: malloc error parser var", STDERR_FILENO);
		return (NULL);
	}
	var->in = NULL;
	var->out = NULL;
	var->amount_of_words = 0;
	var->old_command = NULL;
	var->command = NULL;
	var->command_list = NULL;
	return (var);
}

int	parse_until_pipe(t_list **tokens, t_token **token, t_parser_var *var)
{
	*token = (t_token *)(*tokens)->content;
	while (*tokens && (*token)->type != WORD && (*token)->type != PIPE)
	{
		if (parse_redirect(tokens, token, var))
			return (EXIT_FAILURE);
	}
	while (*tokens && (*token)->type == WORD)
	{
		if (parse_word(tokens, token, var))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Goes through the complete list of tokens and hands them to the right
// parse function (see parser_tokens.c). This produces a linked list of 
// input redirections, a linked list of output redirections and a
// char **command with the command and all its options/arguments
// Combines all three in linked list of of type t_command.
t_command	*parse_tokens(t_list **list_start)
{
	t_parser_var	*var;
	t_token			*token;
	t_list			*tokens;
	t_command		*command_list;

	tokens = *list_start;
	var = init_parser_vars();
	if (!var)
		return (terminate_token_list_error(list_start));
	while (tokens)
	{
		reset_vars(&tokens, &token, var);
		while (tokens && token->type != PIPE)
		{
			if (parse_until_pipe(&tokens, &token, var))
				return (parser_terminate_error(list_start, var));
		}
		if (tokens && token->type == PIPE)
		{
			if (parse_pipe(&tokens, &token, var))
				return (parser_terminate_error(list_start, var));
		}
		add_command_to_list(var);
	}
	command_list = var->command_list;
	free(var);
	return (command_list);
}
