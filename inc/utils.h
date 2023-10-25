/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 14:33:52 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/25 15:04:20 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "./types.h"

// utils/hashnode_functions.c
t_hnode		*new_hash_node(char *key, char *value);
t_hnode		*hasharray_last(t_hnode *array);
int			hasharray_size(t_hnode *array);

// utils/hashnode_add_delete.c 
void		hasharray_add_back(t_hnode **array, t_hnode *new);
void		hasharray_add_front(t_hnode **array, t_hnode *new);
void		hasharray_delone(t_hnode *node);
void		hasharray_clear(t_hnode **array);

// process_add_delete.c 
t_process	*processnode_new(pid_t pid);
void		process_add_back(t_process **lst, t_process *new);
void		process_add_front(t_process **lst, t_process *new);
void		process_delone(t_process *node);
void		process_clear(t_process **lst);

// process_functions.c 
t_process	*process_last(t_process *lst);
t_process	*process_make_add_node(t_process **lst, pid_t pid);

#endif
