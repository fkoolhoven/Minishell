/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   types.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 11:01:53 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/15 13:34:11 by jhendrik      ########   odam.nl         */
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

#endif
