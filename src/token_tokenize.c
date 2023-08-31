/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:36:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/31 16:37:32 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	tokenize_double_quote(t_token *token, char *input, int *i)
{
	int	strlen;

	strlen = find_next_quote(input[*i], input, i);
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen - 1, strlen);
}

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
	while (!char_is_operator(input[*i]) && !isspace(input[*i]) && !char_is_quote(input[*i]) && input[*i])
	{
		strlen++;
		(*i)++;
	}
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen, strlen);
}

char *get_filename_or_delimiter(char *input, int *i)
{
	char	*filename;
	int		strlen;

	strlen = 0;
	while (isspace(input[*i]))
		(*i)++;
	if (!input[*i] || char_is_operator(input[*i]))
	{
		printf("missing filename for redirection\n");
		exit(EXIT_FAILURE);
	}
	while (!isspace(input[*i]) && input[*i])
	{
		(*i)++;
		strlen++;
	}
	filename = ft_substr(input, *i - strlen, strlen);
	return (filename);
}

void	tokenize_operator(t_token *token, char *input, int *i)
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
		token->value = NULL;
	}
	(*i)++;
	if (token->type != PIPE)
	{
		token->value = get_filename_or_delimiter(input, i);
	}
}