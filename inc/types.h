/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:01:53 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/12 16:00:39 by fkoolhov         ###   ########.fr       */
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
	HEREDOC_UNLINKED
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
	int		size;
	t_hnode	**array;
}	t_htable;

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

typedef struct s_heredoc_var
{
	int			fd;
	char		*input;
	t_htable	*env;
}	t_heredoc_var;

typedef struct s_exec_var
{
	t_command	*cmnd_list;
	t_htable	*env;
	char		**env_str;
	int			*fd_pipe;
	int			last_cmnd;
	int			exit_status;
	int			fd_read;
	pid_t		process;
}	t_exec_var;

typedef struct s_parser_var
{
	t_redirect	*in;
	t_redirect	*out;
	int			amount_of_words;
	char		**old_command;
	char		**command;
	t_command	*command_list;
}	t_parser_var;

typedef int		(*t_f_bltin)(t_exec_var *, t_command *);
typedef void	(*t_sighandle)(int);

#endif
