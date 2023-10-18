/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:21:03 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/18 12:27:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define INCORRECT_USAGE 2

// errors_parser.c
void	*malloc_error_return_null(char *message);
int		malloc_error_return_failure(char *message);
void	*syntax_error_return_null(char *message);
int		syntax_error_return_failure(char *message);

// errors_exec.c
int		exec_error_swap(int fd_in, int fd_out, t_exec_var *var);
int		exec_error_child_denied(t_exec_var *var, char *v_cmd, t_command *cmd);
int		exec_error_child_notfound(t_exec_var *var, char *v_cmd, t_command *cmd);
int		exec_error_parent(t_exec_var *var);
int		exec_error_parent_nopipe(t_exec_var *var);

#endif