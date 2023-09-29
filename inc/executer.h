/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:59:43 by jhendrik          #+#    #+#             */
/*   Updated: 2023/09/29 15:49:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "./types.h"

// exec_utils.c ------------------------------------------
int				size_cmndlist(t_command *cmnd_list);

// exec.c -------------------------------------------------
int				execute(t_command *cmnd_list, t_htable *environ);
void			child_process(t_exec_var *var, int j);
void			parent_process(t_exec_var *var, int j);

// builtins
int				export(t_exec_var *s_exec_var, t_command *s_command);

#endif
