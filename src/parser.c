/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:59:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 20:09:22 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This file is the basis for the parsing process. Right now it also includes
// some functions for testing purposes. Didn't check for leaks yet.

// PRINT FUNCTIONS FOR TESTING PURPOSES:
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
		print_string_array(list->command);
		printf("\n\nOUTPUTS:\n");
		print_redirections(list->out);
		list = list->next;
	}
}

// END OF TEST FUNCTIONS! BELOW PROGRAM FUNCTIONS!

// Adds new command struct (node) to command list.
void	add_command_to_list(t_parser_var *vars)
{
	t_command	*new_command;

	if (!vars->command_list)
	{
		vars->command_list = lstnew_command(vars->command, vars->in, vars->out);
		if (vars->command_list == NULL)
		{
			printf("Error allocating for command_list\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_command = lstnew_command(vars->command, vars->in, vars->out);
		if (new_command == NULL)
		{
			printf("Error allocating for new_command\n");
			exit(EXIT_FAILURE);
		}
		lstadd_back_command(&vars->command_list, new_command);
	}
}

// Resets the variables needed for creating another command struct.
void	reset_vars(t_list **tokens, t_token **token, t_parser_var *vars)
{
	vars->in = NULL;
	vars->out = NULL;
	vars->command = NULL;
	vars->amount_of_words = 0;
	*token = (t_token *)(*tokens)->content;
}

// Initializes the vars struct and its contents.
t_parser_var	*init_parser_vars(void)
{
	t_parser_var	*vars;

	vars = malloc(sizeof(t_parser_var));
	if (vars == NULL)
	{
		ft_putendl_fd("minishell: malloc error parser vars", STDERR_FILENO);
		return (NULL);
	}
	vars->in = NULL;
	vars->out = NULL;
	vars->amount_of_words = 0;
	vars->old_command = NULL;
	vars->command = NULL;
	vars->command_list = NULL;
	return (vars);
}

int	parse_until_pipe(t_list **tokens, t_token **token, t_parser_var *vars)
{
	*token = (t_token *)(*tokens)->content;
	while (*tokens && (*token)->type != WORD && (*token)->type != PIPE)
	{
		if (parse_redirect(tokens, token, vars))
			return (EXIT_FAILURE);
	}
	while (*tokens && (*token)->type == WORD)
	{
		if (parse_word(tokens, token, vars))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Goes through the complete list of tokens and hands them to the right
// parse function (see parser_tokens.c). This produces a linked list of 
// input redirections, a linked list of output redirections and a
// char **command with the command and all its options/arguments
// Combines all three in linked list of of type t_command.
int	parse_tokens(t_list *tokens)
{
	t_parser_var	*vars;
	t_token			*token;

	vars = init_parser_vars();
	if (!vars)
		return (EXIT_FAILURE);
	while (tokens)
	{
		reset_vars(&tokens, &token, vars);
		while (tokens && token->type != PIPE)
		{
			if (parse_until_pipe(&tokens, &token, vars))
				return (EXIT_FAILURE);
		}
		if (tokens && token->type == PIPE)
		{
			if (parse_pipe(&tokens, &token, vars))
				return (EXIT_FAILURE);
		}
		if (vars->command)
			add_command_to_list(vars);
	}
	print_command_list(vars->command_list);
	free(vars);
	return (EXIT_SUCCESS);
}
