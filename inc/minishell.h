/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 15:21:27 by jhendrik      ########   odam.nl         */
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

typedef struct s_hash_node
{
	char	*key;
	char	*value;
	struct s_hash_node	*next;
}	t_hash_node;

typedef struct s_hash_table
{
	int	size;
	t_hash_node	**array;
}	t_hash_table;

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

// utils/hashnode_functions.c
t_hash_node	*new_hash_node(char *key, char *value);
t_hash_node	*hasharray_last(t_hash_node *array);
void		hasharray_add_back(t_hash_node **array, t_hash_node *new);
void		hasharray_add_front(t_hash_node **array, t_hash_node *new);
void		hasharray_delone(t_hash_node *node);
void		hasharray_clear(t_hash_node **array);
int			hasharray_size(t_hash_node *array);

//utils/init_env.c
t_hash_table	*init_env(char **envp);
void			terminate_hashtable(t_hash_table *env_table);
t_hash_node		**init_hash_array(t_hash_table *env_table, char **envp);
void			terminate_hasharray(t_hash_node ***head, int size);
t_hash_node		**hasharray_calloc(size_t cnt, size_t size);
int				give_hash_index(char *key, t_hash_table *env_table);
void	print_hashtable(t_hash_table *env_table);
void	print_hasharray(t_hash_table *env_table, t_hash_node **head);

#endif
