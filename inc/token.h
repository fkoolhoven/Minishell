/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 12:00:08 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

// token.c
t_list	*tokenize_input(char *input);
void	print_tokens(t_list *tokens);

// token_test.c TEST FUNCTIONS!
void	print_tokens(t_list *tokens);

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
bool	found_expandable(char *input, int i);
bool	next_token_is_found(char *input, int i);
bool	token_contains_expandable(char *str);

#endif