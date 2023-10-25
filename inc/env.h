/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:29:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/25 14:35:59 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// env_functions/env_terminate.c 
void		terminate_hasharray(t_hnode ***head, int size);
void		terminate_hashtable(t_htable *env_table);

// env_functions/env_utils.c 
int			give_hash_index(char *key, t_htable *env_table);
t_hnode		**hasharray_calloc(size_t cnt, size_t size);
char		*give_key(char *variable);
char		*give_value(char *variable);

// env_functions/init_env.c 
t_hnode		**init_hash_array(t_htable *env_table, char **envp);
t_htable	*init_env(char **envp);

// env_functions/init_keyvalue_pairs.c 
int			init_keyvalue(t_hnode ***head, t_htable *env_table, char **envp);

// env_functions/add_delete_pair.c 
int			add_pair(t_htable *env, char *key, char *value);
int			delete_pair(t_htable *env, char *key);

// env_functions/find_key.c 
t_hnode		*find_env_valuenode(t_htable *env, char *key);
char		*find_env_value(t_htable *env, char *key);

// env_functions/split_first_occurance.c 
char		**split_first_occurance(char const *s, char c);

// env_functions/convert_to_strarray.c 
char		**convert_htable_to_strarray(t_htable *env);

// env_functions/convert_utils.c 
int			size_table(t_htable *env);
char		*give_envstr(t_hnode *node);

#endif
