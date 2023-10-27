/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 17:19:48 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define VALUE_NOT_FOUND -1

// token.c
t_list	*tokenizer(char *input, int *exit_code);
t_token	*initialize_token(void);

// token_tokenize.c
int		tokenize_word(t_token *token, char *input, int *i);
int		tokenize_operator(t_token *token, char *input, int *i, int *exit_code);

// token_quotes.c
int		remove_quotes_from_tokens(t_list **list_start, int *exit_code);

// token_utils.c
bool	char_is_operator(char c);
int		calculate_strlen_for_token_value(char *input, int *i);
int		find_next_quote(char *input, int i);

// token_terminate.c
void	terminate_token(t_list *token);
void	terminate_token_list(t_list **list_start);
void	terminate_token_list_error(t_list **list_start);
void	*terminate_token_list_error_null(t_list **list_start);
int		terminate_token_list_error_failure(t_list **list_start);

#endif