/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtins.h                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/11 10:39:26 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/16 13:18:39 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <linux/limits.h>
# include "./types.h"

// cd.c -----------------------------------------
int	bltin_cd(t_exec_var *var, t_command *cmnd);

// cd_utils.c -----------------------------------
int	cd_give_args_count(char **command);
int	cd_change_env(t_exec_var *var, char *new_path);
int	cd_put_error(char *message, char *key, char *path);
void	cd_move(char *new_path, int start, int end, int size);
int	cd_find_prevdir(char *new_path, int end);

// cd_curpath.c ---------------------------------
int	cd_change_with_path(t_exec_var *var, char *path);

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
