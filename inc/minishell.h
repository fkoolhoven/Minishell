/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 10:44:38 by jhendrik      ########   odam.nl         */
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
	char				*key;
	char				*value;
	struct s_hash_node	*next;
}	t_hnode;

typedef struct s_hash_table
{
	int			size;
	t_hnode	**array;
}	t_htable;

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
t_hnode	*new_hash_node(char *key, char *value);
t_hnode	*hasharray_last(t_hnode *array);
int		hasharray_size(t_hnode *array);

// utils/hashnode_add_delete.c 
void	hasharray_add_back(t_hnode **array, t_hnode *new);
void	hasharray_add_front(t_hnode **array, t_hnode *new);
void	hasharray_delone(t_hnode *node);
void	hasharray_clear(t_hnode **array);

// env_functions/env_terminate.c 
void	terminate_hasharray(t_hnode ***head, int size);
void	terminate_hashtable(t_htable *env_table);

// env_functions/env_utils.c 
int		give_hash_index(char *key, t_htable *env_table);
t_hnode	**hasharray_calloc(size_t cnt, size_t size);
char	*give_key(char *variable);
char	*give_value(char *variable);

// env_functions/init_env.c 
t_hnode	**init_hash_array(t_htable *env_table, char **envp);
t_htable	*init_env(char **envp);

// env_functions/init_keyvalue_pairs.c 
int	init_keyvalue(t_hnode ***head, t_htable *env_table, char **envp);

// env_functions/add_delete_pair.c 
int	add_pair(t_htable *env, char *key, char *value);
int	delete_pair(t_htable *env, char *key);

// env_functions/find_key.c 
t_hnode	*find_env_valuenode(t_htable *env, char *key);
char	*find_env_value(t_htable *env, char *key);

// env_functions/split_first_occurance.c 
char	**split_first_occurance(char const *s, char c);

// env_functions/test_ft.c 
void	print_hasharray(t_htable *env_table, t_hnode **head);
void	print_strarray(char **envp);
void	print_hashtable(t_htable *env_table);
void	print_hashnode(t_hnode *node, t_htable *env);

#endif
