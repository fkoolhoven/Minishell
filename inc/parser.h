/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/05 17:38:32 by fkoolhov         ###   ########.fr       */
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
	char				**command; // contains one command and its arguments, to be passed to execve [0] is command, rest is args
	struct s_redirect	*out; // contains a list of all output redirections in order (pipe, outfile or append outfile)
	struct s_redirect	*in; // contains a list of all input redirections in order (pipe, heredoc or infile)
	struct s_command	*next;
}	t_command;

// parser.c
void	parse_tokens(t_list *tokens);

// parser_lists.c
t_command	*lstlast_command(t_command *lst);
t_command	*lstnew_command(char **command, t_redirect *in, t_redirect *out);
void		lstadd_back_command(t_command **lst, t_command *new);
t_redirect	*lstnew_redirect(int type, char *value);
void		lstadd_back_redirect(t_redirect **lst, t_redirect *new);

// parser_utils.c
bool	token_is_input_type(t_token *token);
bool	token_is_output_type(t_token *token);


#endif