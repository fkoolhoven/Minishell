/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:59:43 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/11 12:08:28 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./types.h"
# include <sys/wait.h>
# include <fcntl.h>

// heredoc_handler.c ------------------------------------
int	manage_heredocs(t_command *command_list, t_htable *env);

// input_heredoc.c --------------------------------------
void	input_to_heredoc(int fd, char *limit, t_htable *env);

// heredoc_utils.c 
void	put_str_between(t_heredoc_var var, int first, int last);
void	expand_put_var(t_heredoc_var var, int *first, int last);

// manage_one_heredoc.c 
int	manage_one_heredoc(char *filename, t_redirect *node, t_htable *env);

// heredoc_unlinker.c 
void	heredoc_unlinker(t_command *command_list);

// test_heredoc.c --------------------------------------------
void	display_file(char *filename);
void	display_heredocs(t_command *cmnd_list);
void	test_heredoc(t_command *cmnd_list, t_htable *env);

// exec_utils.c ------------------------------------------
int		size_cmndlist(t_command *cmnd_list);
void	create_all_outfiles(t_exec_var *var);

// swap_fds.c -----------------------------------------------
int		swap_filedescriptors(t_exec_var *var, t_command *cmnd);

// give_fds.c ------------------------------------------------
int		give_input_fd(t_redirect *in);
int		give_output_fd(t_redirect *out);

// exec_builtins.c ---------------------------------------
int	check_if_builtin(t_exec_var *var, t_command *command);
int	execute_builtin(t_exec_var *var, t_command *cmnd, int bltin);

// exec.c -------------------------------------------------
int	execute(t_command *cmnd_list, t_htable *environ, int exit_status);

// processes.c --------------------------------------------
int	child_process(t_exec_var *var, t_command *cmnd);
int	child_process_onecmnd(t_exec_var *var, t_command *cmnd);
int	parent_process(t_exec_var *var, int j);
int	parent_one_command(t_exec_var *var);

// errors.c -----------------------------------------------
int	exec_error_swap(int fd_in, int fd_out, t_exec_var *var);
int	exec_error_child_denied(t_exec_var *var, char *val_cmnd, t_command *cmnd);
int	exec_error_child_notfound(t_exec_var *var, char *val_cmnd, t_command *cmnd);
int	exec_error_parent(t_exec_var *var);
int	exec_error_parent_nopipe(t_exec_var *var);

// valid_path.c ---------------------------------------------
char	*find_command_path(t_exec_var *var, t_command *cmnd);

// terminate_execvar.c --------------------------------------
void	terminate_execvar(t_exec_var *var);

#endif
