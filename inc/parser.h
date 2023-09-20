/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 18:41:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redirect
{
	enum e_type			type;
	char				*value;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**command;
	struct s_redirect	*out;
	struct s_redirect	*in;
	struct s_command	*next;
}	t_command;

typedef struct s_parser_var
{
	t_redirect	*in;
	t_redirect	*out;
	size_t		amount_of_words;
	char		**old_command;
	char		**command;
	t_command	*command_list;
}	t_parser_var;

// parser.c
int			parse_tokens(t_list *tokens);

// parser_lists.c
t_command	*lstlast_command(t_command *lst);
t_command	*lstnew_command(char **command, t_redirect *in, t_redirect *out);
void		lstadd_back_command(t_command **lst, t_command *new);
t_redirect	*lstnew_redirect(int type, char *value);
void		lstadd_back_redirect(t_redirect **lst, t_redirect *new);

// parser_parse.c
int			parse_word(t_list **tokens, t_token **token, t_parser_var *vars);
int			parse_redirect(t_list **tokens, t_token **token, t_parser_var *vars);
int			parse_pipe(t_list **tokens, t_token **token, t_parser_var *vars);

// parser_utils.c
bool		token_is_input_type(t_token *token);
bool		token_is_output_type(t_token *token);

#endif