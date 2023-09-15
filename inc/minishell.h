/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/15 11:08:08 by jhendrik      ########   odam.nl         */
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
# include "./types.h"
# include "./exec.h"
# include <ctype.h> // we should add our own isspace() to libft!

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

// heredoc_handler.c 
int	manage_heredocs(t_command *command_list);

// utils/hashnode_functions.c
t_hash_node	*new_hash_node(char *key, char *value);
t_hash_node	*hasharray_last(t_hash_node *array);
void		hasharray_add_back(t_hash_node **array, t_hash_node *new);
void		hasharray_add_front(t_hash_node **array, t_hash_node *new);
void		hasharray_delone(t_hash_node *node);
void		hasharray_clear(t_hash_node **array);
int			hasharray_size(t_hash_node *array);

//utils/init_env.c
t_hash_table	*init_env();
void			terminate_hashtable(t_hash_table *env_table);
t_hash_node		**init_hash_array(t_hash_table *env_table);
void			terminate_hasharray(t_hash_node ***head, int size);
t_hash_node		**hasharray_calloc(size_t cnt, size_t size);
int				give_hash_index(char *key, t_hash_table *env_table);

#endif
