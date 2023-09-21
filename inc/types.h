/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:01:53 by jhendrik          #+#    #+#             */
/*   Updated: 2023/09/21 18:23:26 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

enum e_type
{
	WORD,
	PIPE,
	HEREDOC,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	HEREDOC_INFILE,
	HEREDOC_FAIL
};

typedef struct s_token
{
	enum e_type	type;
	char		*value;
	bool		expand;
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

typedef struct s_exec_var
{
	t_command	*cmnd_list;
	char		**env;
	int			fd_pipe[2];
	int			last_cmnd;
	pid_t		process;
}	t_exec_var;

typedef struct s_parser_var
{
	t_redirect	*in;
	t_redirect	*out;
	size_t		amount_of_words;
	char		**old_command;
	char		**command;
	t_command	*command_list;
}	t_parser_var;

typedef int	(*t_f_bltin)(t_exec_var, t_command);

#endif
