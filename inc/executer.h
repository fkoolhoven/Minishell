/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:59:43 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/20 11:24:30 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "./types.h"
# include <sys/wait.h>
# include <fcntl.h>

// heredoc_handler.c
int		manage_heredocs(t_command *command_list, t_htable *env);

// input_heredoc.c
void	input_to_heredoc(int fd, char *limit, t_htable *env);

// heredoc_utils.c 
void	put_str_between(t_heredoc_var var, int first, int last);
void	expand_put_var(t_heredoc_var var, int *first, int last);

// manage_one_heredoc.c 
int		manage_one_heredoc(char *filename, t_redirect *node, t_htable *env);

// heredoc_unlinker.c 
void	heredoc_unlinker(t_command *command_list);

// exec_utils.c
int		size_cmndlist(t_command *cmnd_list);
void	create_all_outfiles(t_exec_var *var);

// swap_fds.c
int		swap_filedescriptors(t_exec_var *var, t_command *cmnd);

// swap_fd_mini.c 
int		swap_back_in_minishell(t_exec_var *var, int fd_stdin, int fd_stdout);
int		swap_mini(t_exec_var *var, t_command *cmnd, int *fd_in, int *fd_out);

// give_fds.c
int		give_input_fd(t_redirect *in);
int		give_output_fd(t_redirect *out);

// exec_builtins.c
int		check_if_builtin(t_exec_var *var, t_command *command);
int		execute_builtin(t_exec_var *var, t_command *cmnd, int bltin);

// exec.c
int		execute(t_command *cmnd_list, t_htable *env, int estatus, char *cpath);

// processes.c
int		child_process(t_exec_var *var, t_command *cmnd);
int		child_process_onecmnd(t_exec_var *var, t_command *cmnd);
int		parent_process(t_exec_var *var, int j);
int		parent_one_command(t_exec_var *var);

// valid_path.c
char	*find_command_path(t_exec_var *var, t_command *cmnd);

// terminate_execvar.c
void	terminate_execvar(t_exec_var *var);

#endif
