/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:03:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/18 15:05:55 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe_token(t_list **tokens, t_token **token,
	t_parser_var *var, int *exit_code)
{
	if (add_redirect_to_list(&var->out, (*token)->type, (*token)->value))
		return (EXIT_FAILURE);
	*tokens = (*tokens)->next;
	if (*tokens)
	{
		*token = (t_token *)(*tokens)->content;
		if ((*token)->type == PIPE)
			return (syntax_error_return_failure("subsequent pipes", exit_code));
	}
	else
		return (syntax_error_return_failure("missing command", exit_code));
	return (EXIT_SUCCESS);
}

int	parse_redirect_token(t_list **tokens, t_token **current, t_parser_var *var)
{
	t_token	*token;
	int		error;

	token = *current;
	if (token_is_input_type(token))
		error = add_redirect_to_list(&var->in, token->type, token->value);
	else
		error = add_redirect_to_list(&var->out, token->type, token->value);
	if (error != EXIT_SUCCESS)
		return (error);
	*tokens = (*tokens)->next;
	if (*tokens)
		*current = (t_token *)(*tokens)->content;
	return (EXIT_SUCCESS);
}

static int	calculate_amount_of_words(t_list *tokens, t_token *token)
{
	int	amount_of_words;

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

int	parse_word_token(t_list **tokens, t_token **token, t_parser_var *var)
{
	int	i;

	var->old_command = var->command;
	var->amount_of_words += calculate_amount_of_words(*tokens, *token);
	var->command = ft_calloc(var->amount_of_words + 1, sizeof(char *));
	if (var->command == NULL)
		return (malloc_error_return_failure("parser"));
	i = 0;
	while (var->old_command && var->old_command[i])
	{
		var->command[i] = var->old_command[i];
		i++;
	}
	while (i < var->amount_of_words)
	{
		var->command[i] = (*token)->value;
		*tokens = (*tokens)->next;
		if (*tokens)
			*token = (t_token *)(*tokens)->content;
		i++;
	}
	if (var->old_command)
		free(var->old_command);
	return (EXIT_SUCCESS);
}
