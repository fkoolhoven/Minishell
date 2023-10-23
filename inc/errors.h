/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:21:03 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/23 12:38:51 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define INCORRECT_USAGE 2

// errors_parser.c
void	*malloc_error_return_null(char *message);
int		malloc_error_return_failure(char *message);
void	*syntax_error_return_null(char *message, int *exit_code);
int		syntax_error_return_failure(char *message, int *exit_code);

// errors_exec_swap.c
int		swap_error_child(int fd_in, int fd_out, t_exec_var *var);
int		swap_error_parent(int fd_in, int fd_out, t_exec_var *var);

// errors_exec_process.c 
int		exec_error_child_denied(t_exec_var *var, char *v_cmd, t_command *cmd);
int		exec_error_child_notfound(t_exec_var *var, char *v_cmd, t_command *cmd);
int		exec_error_parent(t_exec_var *var);
int		exec_error_parent_nopipe(t_exec_var *var);

#endif
