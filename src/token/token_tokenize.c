/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:36:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 16:48:12 by fkoolhov         ###   ########.fr       */
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
	{
		ft_putendl_fd("alloc fail word", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*get_filename_or_delimiter(char *input, int *i)
{
	char	*filename;
	int		filename_len;

	while (ft_isspace(input[*i]) && input[*i])
		(*i)++;
	if (!input[*i] || char_is_operator(input[*i]))
	{
		ft_putendl_fd("missing filename for redirection", STDERR_FILENO);
		return (NULL);
	}
	filename_len = calculate_strlen_for_token_value(input, i);
	filename = ft_substr(input, *i - filename_len, filename_len);
	if (filename == NULL)
	{
		ft_putendl_fd("alloc fail filename", STDERR_FILENO);
		return (NULL);
	}
	return (filename);
}

int	tokenize_infiles_and_outfiles(t_token *token, char *input, int *i)
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
	(*i)++;
	token->value = get_filename_or_delimiter(input, i);
	if (!token->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	tokenize_operator(t_token *token, char *input, int *i)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (tokenize_infiles_and_outfiles(token, input, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (input[*i] == '|')
	{
		token->type = PIPE;
		token->value = ft_calloc(2, sizeof(char));
		if (token->value == NULL)
		{
			ft_putendl_fd("alloc fail pipe", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		token->value[0] = '|';
		(*i)++;
	}
	return (EXIT_SUCCESS);
}
