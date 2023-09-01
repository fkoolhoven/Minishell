/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/31 16:43:12 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./../libs/libft/include/libft.h"
# include <ctype.h> // we should add our own isspace() to libft!

enum e_type
{
	WORD,
	PIPE,
	HEREDOC,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND
};

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}	t_token;

// token.c
void	tokenize_input(char *input);

// token_tokenize.c
void	tokenize_double_quote(t_token *token, char *input, int *i);
void	tokenize_single_quote(t_token *token, char *input, int *i);
void	tokenize_word(t_token *token, char *input, int *i);
void	tokenize_operator(t_token *token, char *input, int *i);

// token_utils.c
bool	char_is_single_quote(char c);
bool	char_is_double_quote(char c);
bool	char_is_quote(char c);
bool	char_is_operator(char c);

#endif
