/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec.h                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/15 10:59:43 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/15 13:36:56 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./types.h"

// exec_utils.c ------------------------------------------
int	size_cmndlist(t_command *cmnd_list);

// exec.c -------------------------------------------------
int	execute(t_command *cmnd_list, char **environ);
void	child_process(t_exec_var *var, int j);
void	parent_process(t_exec_var *var, int j);

#endif
