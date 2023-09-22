/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:59:43 by jhendrik          #+#    #+#             */
/*   Updated: 2023/09/21 18:28:40 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./types.h"

// exec_utils.c ------------------------------------------
int				size_cmndlist(t_command *cmnd_list);

// exec.c -------------------------------------------------
int				execute(t_command *cmnd_list, char **environ);
void			child_process(t_exec_var *var, int j);
void			parent_process(t_exec_var *var, int j);

// print_hashtable.c
void			st_print_hashnodes(t_hash_node *head);
void			st_print_hasharray(t_hash_table *env_table);
void			st_print_hashtable(t_hash_table *env_table);

// init_env.c
t_hash_table	*init_env(void);
void			terminate_hashtable(t_hash_table *env_table);

// hashnode_functions.c
t_hash_node		*new_hash_node(char *key, char *value);
void			hasharray_add_back(t_hash_node **array, t_hash_node *new);
void			hasharray_clear(t_hash_node **array);

#endif
