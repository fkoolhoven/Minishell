/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:59:43 by jhendrik          #+#    #+#             */
/*   Updated: 2023/11/03 10:11:21 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "./types.h"
# include <sys/wait.h>
# include <fcntl.h>

// heredoc_handler.c
int		manage_heredocs(t_command *command_list, t_htable *env, int ecode);

// input_heredoc.c
void	input_to_heredoc(int fd, char *limit, t_htable *env, int ecode);

// heredoc_utils.c 
void	put_str_between(t_heredoc_var var, int first, int last);
void	exp_not_alldols(t_heredoc_var var, int *first, int *last, int ecode);
char	*give_between_vars(char *user_input, int first, int last);

// manage_one_heredoc.c 
int		man_one_here(char *fname, t_redirect *node, t_htable *env, int ecode);

// heredoc_unlinker.c 
void	heredoc_unlinker(t_command *command_list);

// heredoc_bool.c 
bool	input_is_all_dollars(char *input);
bool	is_var_notdollar(int c);

// heredoc_expandinput.c 
void	expand_put_var(t_heredoc_var var, int *first, int *last, int ecode);
int		*skip_dollars(t_heredoc_var var, int *first, int *last);
char	*key_quotes(t_heredoc_var var, int *first, int *last, char ch);
char	*key_noquotes(t_heredoc_var var, int *first, int *last);

// exec_utils.c
int		size_cmndlist(t_command *cmnd_list);
void	create_all_outfiles(t_exec_var *var);
bool	heredoc_infile_found(t_redirect *in);
int		wait_for_all(t_process *lst);

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

// exec_one_cmnd.c 
int		execute_one_cmnd(t_exec_var *var);

// processes.c
int		child_process(t_exec_var *var, t_command *cmnd);
int		child_process_onecmnd(t_exec_var *var, t_command *cmnd);
int		parent_process(t_exec_var *var, int j);
int		parent_one_command(t_exec_var *var, t_process *ch_proclst);

// valid_path.c
char	*find_command_path(t_exec_var *var, t_command *cmnd);

// terminate_execvar.c
void	terminate_execvar_child(t_exec_var **var);
void	terminate_execvar_parent(t_exec_var **var);
void	terminate_execvar_exit(t_exec_var **var);

// close_fds.c 
void	close_pipes(t_exec_var *var);
void	close_given_pipe(int *fds);
void	close_read_end(int *fds);
void	close_write_end(int *fds);

#endif
