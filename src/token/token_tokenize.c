/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:36:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 16:44:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// last function is too long

int	find_next_quote(char quote, char *input, int *i)
{
	int	strlen;

	strlen = 0;
	(*i)++;
	while (input[*i] != quote)
	{
		(*i)++;
		strlen++;
	}
	(*i)++;
	return (strlen);
}

// Tokenizes everything between double quotes, also checking for $ as expandable
void	tokenize_double_quote(t_token *token, char *input, int *i)
{
	int	strlen;

	strlen = find_next_quote(input[*i], input, i);
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen - 1, strlen);
	if (token_contains_expandable(token->value))
		token->expand = true;
}

// Tokenizes everything between double quotes, seeing $ as regular character
void	tokenize_single_quote(t_token *token, char *input, int *i)
{
	int	strlen;

	strlen = find_next_quote(input[*i], input, i);
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen - 1, strlen);
}

void	tokenize_word(t_token *token, char *input, int *i)
{
	int	strlen;

	strlen = 0;
	while (!ft_isspace(input[*i]) && input[*i] && !next_token(input, *i))
	{
		strlen++;
		(*i)++;
	}
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen, strlen);
	if (token_contains_expandable(token->value))
		token->expand = true;
}

char	*get_filename_or_delimiter(char *input, int *i)
{
	char	*filename;
	int		strlen;

	strlen = 0;
	while (ft_isspace(input[*i]) && input[*i])
		(*i)++;
	if (!input[*i] || char_is_operator(input[*i]))
	{
		ft_putendl_fd("missing filename for redirection", STDERR_FILENO);
		return (NULL);
	}
	while (!ft_isspace(input[*i]) && input[*i] && !next_token(input, *i))
	{
		(*i)++;
		strlen++;
	}
	filename = ft_substr(input, *i - strlen, strlen);
	return (filename);
}

int	tokenize_operator(t_token *token, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			token->type = HEREDOC;
			(*i)++;
		}
		else
			token->type = INFILE;
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			token->type = OUTFILE_APPEND;
			(*i)++;
		}
		else
			token->type = OUTFILE;
	}
	else if (input[*i] == '|')
	{
		token->type = PIPE;
		token->value = ft_calloc(2, sizeof(char));
		token->value[0] = '|';
	}
	(*i)++;
	if (token->type != PIPE)
	{
		token->value = get_filename_or_delimiter(input, i);
		if (!token->value)
			return (EXIT_FAILURE);
		if (token->value[0] == '$')
			token->expand = true;
	}
	return (EXIT_SUCCESS);
}
