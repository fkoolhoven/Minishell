/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:39:26 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/18 12:32:28 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./types.h"

// cd.c
int		bltin_cd(t_exec_var *var, t_command *cmnd);

// echo.c
int		bltin_echo(t_exec_var *var, t_command *command);

// env.c
int		bltin_env(t_exec_var *var, t_command *cmnd);

// exit.c
int		bltin_exit(t_exec_var *var, t_command *cmnd);

// export.c
int		bltin_export(t_exec_var *var, t_command *cmnd);
char	*get_value(char *command, int key_end);

// pwd.c
int		bltin_pwd(t_exec_var *var, t_command *command);

// unset.c
int		bltin_unset(t_exec_var *var, t_command *cmnd);

#endif