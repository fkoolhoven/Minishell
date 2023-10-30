/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:01:53 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/30 19:43:39 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "./../libs/libft/include/libft.h"

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
	bool		expansion_beginning;
	bool		expansion_end;
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

typedef struct s_process
{
	pid_t				process;
	struct s_process	*next;
}	t_process;

typedef struct s_exec_var
{
	t_command	*cmnd_list;
	t_htable	*env;
	char		**env_str;
	char		*cur_path;
	int			*fd_pipe;
	int			last_cmnd;
	int			exit_status;
	int			*prev_pipe;
	int			process;
	t_process	*process_lst;
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

typedef struct s_expander_var
{
	t_list	*tokens;
	t_token	*token;
	char	*new_value;
	char	**split_value;
	bool	cat_begin;
	bool	cat_end;
	int		key_start;
	int		key_len;
	int		i;
	bool	token_was_split;
	bool	in_double_quotes;
}	t_expander_var;

typedef struct s_trim_var
{
	char	*inset1;
	char	*inset2;
	char	*str;
	char	*trimmed;
	size_t	j;
}	t_trim_var;

typedef int		(*t_f_bltin)(t_exec_var *, t_command *);
typedef void	(*t_sighandle)(int);

#endif
