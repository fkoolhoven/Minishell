/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtins.h                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/06 14:30:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/06 14:47:23 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include "./types.h"

// cd.c -----------------------------------------
int	bltin_cd(t_exec_var *var, t_command *cmnd);

// echo.c ---------------------------------------
int	bltin_echo(t_exec_var *var, t_command *command);

// env.c ----------------------------------------
int	bltin_env(t_exec_var *var, t_command *cmnd);

// exit.c ---------------------------------------
int	bltin_exit(t_exec_var *var, t_command *cmnd);

// export.c -------------------------------------
int	bltin_export(t_exec_var *var, t_command *cmnd);

// pwd.c ----------------------------------------
int	bltin_pwd(t_exec_var *var, t_command *command);

// unset.c --------------------------------------
int	bltin_unset(t_exec_var *var, t_command *cmnd);


#endif
