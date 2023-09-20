/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:03:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 20:07:21 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This file handles the parsing of individual tokens. It turns redirections
// into a linked list of t_redirect type (in and out) and turns words into
// a char **command.

// Adds new redirect struct (node) to redirect list for a certain command
void	add_redirect_to_list(t_redirect **redirect_list, int type, char *value)
{
	t_redirect	*new_redirect;

	if (!*redirect_list)
	{
		*redirect_list = lstnew_redirect(type, value);
		if (*redirect_list == NULL)
		{
			printf("Error allocating for redirect_list\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_redirect = lstnew_redirect(type, value);
		if (new_redirect == NULL)
		{
			printf("Error allocating for new_redirect\n");
			exit(EXIT_FAILURE);
		}
		lstadd_back_redirect(redirect_list, new_redirect);
	}
}

// Calculates amount of words in a sequence of tokens
// to calculate how much space is needed for char **command
size_t	calculate_amount_of_words(t_list *tokens, t_token *token)
{
	size_t	amount_of_words;

	amount_of_words = 0;
	while (tokens && token->type == WORD)
	{
		amount_of_words++;
		tokens = tokens->next;
		if (tokens)
			token = (t_token *)tokens->content;
	}
	return (amount_of_words);
}

// Parses pipe and adds it to the end of out redirections list
// gives error if multiple pipes or input ends with pipe
int	parse_pipe(t_list **tokens, t_token **token, t_parser_var *vars)
{
	add_redirect_to_list(&vars->out, (*token)->type, (*token)->value);
	*tokens = (*tokens)->next;
	if (*tokens)
	{
		*token = (t_token *)(*tokens)->content;
		if ((*token)->type == PIPE)
		{
			ft_putendl_fd("minishell: syntax error near "
				"unexpected token `|'", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		ft_putendl_fd("minishell: syntax error: "
			"line incomplete", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Parses words per command and puts them in char **command
int	parse_word(t_list **tokens, t_token **token, t_parser_var *vars)
{
	size_t	i;

	vars->old_command = vars->command;
	vars->amount_of_words += calculate_amount_of_words(*tokens, *token);
	vars->command = ft_calloc(vars->amount_of_words + 1, sizeof(char *));
	i = 0;
	while (vars->old_command && vars->old_command[i])
	{
		vars->command[i] = vars->old_command[i];
		i++;
	}
	while (i < vars->amount_of_words)
	{
		vars->command[i] = (*token)->value;
		*tokens = (*tokens)->next;
		if (*tokens)
			*token = (t_token *)(*tokens)->content;
		i++;
	}
	if (vars->old_command)
		free(vars->old_command);
	return (EXIT_SUCCESS);
}

// Parses redirections per command and
// adds them to either list of in or out redirections list
int	parse_redirect(t_list **tokens, t_token **token, t_parser_var *vars)
{
	if (token_is_input_type(*token))
		add_redirect_to_list(&vars->in, (*token)->type, (*token)->value);
	else
		add_redirect_to_list(&vars->out, (*token)->type, (*token)->value);
	*tokens = (*tokens)->next;
	if (*tokens)
		*token = (t_token *)(*tokens)->content;
	return (EXIT_SUCCESS);
}
