/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:39:26 by jhendrik          #+#    #+#             */
/*   Updated: 2023/11/01 14:19:20 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include "./types.h"

// cd.c
int		bltin_cd(t_exec_var *var, t_command *cmnd);

// cd_abspath.c 
int		cd_absolute_path(t_exec_var *var, char *path);

// cd_curpath.c 
int		cd_change_with_path(t_exec_var *var, char *path);

// cd_edit_path.c 
void	cd_edit_newpath(char *new_path, int len);

// cd_prev.c 
int		cd_prev_dir(t_exec_var *var);

// cd_strtrim.c 
char	*cd_strtrim(char const *s1, char const *set);

// cd_strtrim_utils.c 
int		cd_lr_c_inset(char const *s1, char const *set);
int		cd_rl_c_inset(char const *s1, char const *set);
char	*cd_nothing_left(void);
size_t	cd_len_trim_between(char *s1, char const *set);

// cd_utils.c 
int		cd_give_args_count(char **command);
int		cd_put_error(char *message, char *key, char *path);
void	cd_ch_curpath(t_exec_var *var, char *npath, char *epath, int status);
void	cd_move(char *new_path, int start, int end, int size);

// cd_change_env.c 
int		cd_change_env(t_exec_var *var, char *new_path, int status);

// echo.c
int		bltin_echo(t_exec_var *var, t_command *command);

// echo_optioncheck.c 
bool	echo_optioncheck(char *option);
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
