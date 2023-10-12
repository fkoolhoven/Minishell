/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/12 16:00:17 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

// token.c
t_list	*tokenizer(char *input);

// token_test.c TEST FUNCTIONS!
void	print_tokens(t_list *tokens);

// token_tokenize.c
int		tokenize_word(t_token *token, char *input, int *i);
int		tokenize_operator(t_token *token, char *input, int *i);

// expand.c
int		expand_tokens(t_list **list_start, t_htable *env);

// expand_variable.c
int		expand_variable(t_token *token, t_htable *env, int *i);

// token_quotes.c
int		remove_quotes_from_tokens(t_list **list_start);

// token_utils.c
bool	char_is_operator(char c);
int		calculate_strlen_for_token_value(char *input, int *i);
int		find_next_quote(char *input, int i);

// token_terminate.c
void	terminate_token_list(t_list **list_start);
void	*terminate_token_list_error(t_list **list_start);


#endif