/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:59:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/25 16:44:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_until_pipe(t_list **tokens, t_token **token, t_parser_var *v)
{
	*token = (t_token *)(*tokens)->content;
	while (*tokens && (*token)->type != WORD && (*token)->type != PIPE)
	{
		if (parse_redirect_token(tokens, token, v))
			return (EXIT_FAILURE);
	}
	while (*tokens && (*token)->type == WORD)
	{
		if (parse_word_token(tokens, token, v))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	parse_one_command(t_list **tokens, t_token **token,
	t_parser_var *var, int *exit_code)
{
	while (*tokens && (*token)->type != PIPE)
	{
		if (parse_until_pipe(tokens, token, var))
			return (EXIT_FAILURE);
	}
	if (*tokens && (*token)->type == PIPE)
	{
		if (parse_pipe_token(tokens, token, var, exit_code))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_parser_var	*init_parser_vars(void)
{
	t_parser_var	*var;

	var = malloc(sizeof(t_parser_var));
	if (var == NULL)
		return (malloc_error_return_null("parser"));
	var->in = NULL;
	var->out = NULL;
	var->old_command = NULL;
	var->command = NULL;
	var->command_list = NULL;
	return (var);
}

// Goes through the complete list of tokens and parses them one
// by one. This produces a linked list of 
// input redirections, a linked list of output redirections and a
// char **command with the command and all its options/arguments.
// Combines all three in linked list with nodes of type t_command.
t_command	*parse(t_list **list_start, int *exit_code)
{
	t_parser_var	*var;
	t_token			*token;
	t_list			*tokens;
	t_command		*command_list;

	tokens = *list_start;
	var = init_parser_vars();
	if (!var)
		return (terminate_token_list_error_null(list_start));
	while (tokens)
	{
		var->in = NULL;
		var->out = NULL;
		var->command = NULL;
		var->amount_of_words = 0;
		token = (t_token *)tokens->content;
		if (parse_one_command(&tokens, &token, var, exit_code) == EXIT_FAILURE)
			return (parser_terminate_error(list_start, var));
		if (add_command_to_list(var) == EXIT_FAILURE)
			return (parser_terminate_error(list_start, var));
	}
	command_list = var->command_list;
	free(var);
	return (command_list);
}
