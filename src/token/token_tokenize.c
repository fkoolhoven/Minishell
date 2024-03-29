/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:36:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 21:03:03 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_word(t_token *token, char *input, int *i)
{
	int		strlen;

	token->type = WORD;
	strlen = calculate_strlen_for_token_value(input, i);
	token->value = ft_substr(input, *i - strlen, strlen);
	if (token->value == NULL)
		return (malloc_error_return_failure("tokenizer"));
	return (EXIT_SUCCESS);
}

static char	*get_filename_or_delimiter(char *input, int *i, int *exit_code)
{
	char	*filename;
	int		filename_len;

	while (ft_isspace(input[*i]) && input[*i])
		(*i)++;
	if (!input[*i] || char_is_operator(input[*i]))
		return (syntax_error_return_null("missing filename", exit_code));
	filename_len = calculate_strlen_for_token_value(input, i);
	filename = ft_substr(input, *i - filename_len, filename_len);
	if (filename == NULL)
		return (malloc_error_return_null("tokenizer"));
	return (filename);
}

static int	tokenize_file_redirects(t_token *token, char *input,
	int *i, int *exit_code)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			token->type = HEREDOC;
		else
			token->type = INFILE;
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			token->type = OUTFILE_APPEND;
		else
			token->type = OUTFILE;
	}
	if (token->type == HEREDOC || token->type == OUTFILE_APPEND)
		(*i)++;
	(*i)++;
	if (char_is_operator(input[*i]))
		return (syntax_error_return_failure("subsequent operators", exit_code));
	token->value = get_filename_or_delimiter(input, i, exit_code);
	if (!token->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	tokenize_operator(t_token *token, char *input, int *i, int *exit_code)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (tokenize_file_redirects(token, input, i, exit_code) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (input[*i] == '|')
	{
		token->type = PIPE;
		token->value = ft_calloc(2, sizeof(char));
		if (token->value == NULL)
			return (malloc_error_return_failure("tokenizer"));
		token->value[0] = '|';
		(*i)++;
	}
	return (EXIT_SUCCESS);
}
