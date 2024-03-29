/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/18 14:03:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser.c
t_command	*parse(t_list **tokens, int *exit_code);

// parser_command_list.c
int			add_command_to_list(t_parser_var *var);

// parser_redirect_list.c
int			add_redirect_to_list(t_redirect **redir_lst, int type, char *value);

// parser_parse_token.c
int			parse_word_token(t_list **toks, t_token **tok, t_parser_var *v);
int			parse_redirect_token(t_list **toks, t_token **tok, t_parser_var *v);
int			parse_pipe_token(t_list **toks, t_token **tok, t_parser_var *v,
				int *exit_code);

// parser_bools.c
bool		char_is_quote(char c);
bool		token_is_input_type(t_token *token);
bool		token_is_output_type(t_token *token);

// parser_terminate.c
void		terminate_command_list(t_command **list_start);
void		*parser_terminate_error(t_list **list_start, t_parser_var *var);

#endif