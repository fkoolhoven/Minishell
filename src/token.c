/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:50 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/31 15:36:56 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include <ctype.h>

bool	char_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

void	print_tokens(t_list *tokens)
{
	while (tokens)
	{
		t_token *current_token = (t_token *)tokens->content;
        printf("type of token = %i\nvalue of token = %s\n", current_token->type, current_token->value);
        tokens = tokens->next;
	}
}

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
	int		strlen;

	strlen = find_next_quote(input[*i], input, i);
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen - 1, strlen);
}

void	tokenize_single_quote(t_token *token, char *input, int *i)
{
	int		strlen;

	strlen = find_next_quote(input[*i], input, i);
	token->type = WORD;
	token->value = ft_substr(input, *i - strlen - 1, strlen);
}

void	tokenize_word(t_token *token)
{
	token->type = WORD;
	token->value = "tokenized word value";
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

t_token	*initialize_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		printf("malloc error token\n");
		exit (EXIT_FAILURE);
	}
	token->type = INFILE;
	token->value = "something";
	return (token);
}

void	add_token_to_list(t_list **tokens, t_token *token)
{
	t_list	*new_node;

	if (*tokens)
	{
		new_node = ft_lstnew(token);
		if (*tokens == NULL)
		{
			printf("malloc error new tokens list node\n");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(tokens, new_node);
	}
	else
	{
		*tokens = ft_lstnew(token);
		if (*tokens == NULL)
		{
			printf("malloc error new tokens list\n");
			exit(EXIT_FAILURE);
		}
	}
}

bool	char_is_single_quote(char c)
{
	if (c == '\'')
		return (true);
	else
		return (false);
}

bool	char_is_double_quote(char c)
{
	if (c == '\"')
		return (true);
	else
		return (false);
}

bool	char_is_quote(char c)
{
	if (char_is_single_quote(c) || char_is_double_quote(c))
		return (true);
	else
		return (false);
}

// << EOF grep \"hello world\" > outfile
void	tokenize_input(char *input)
{
	t_list	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		printf("loop\n");
		while (isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		token = initialize_token();
		add_token_to_list(&tokens, token);
		if (char_is_single_quote(input[i]))
		{
			printf("found single quote\n");
			tokenize_single_quote(token, input, &i);
		}
		else if (char_is_double_quote(input[i]))
		{
			printf("found double quote\n");
			tokenize_double_quote(token, input, &i);
		}
		else if (char_is_operator(input[i]))
		{
			tokenize_operator(token, input, &i);
		}
		else
		{
			tokenize_word(token);
			while (!char_is_operator(input[i]) && !isspace(input[i]) && !char_is_quote(input[i]) && input[i])
				i++;
		}
	}
	print_tokens(tokens);
}
