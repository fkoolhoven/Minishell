/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:19:53 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 18:59:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# define CONTINUE 2

// token_expand.c
int		expand_tokens(t_list **list_start, t_htable *env);

// token_expand_variable.c
int		expand_variable(t_expander_var *var, t_htable *env);

// expand_split_value.c
int		split_token_value(t_expander_var *var);

// expand_update.c
int		update_list(t_expander_var *var);

// expand_split_token.c
int		split_token_beginning_before_key(t_expander_var *var);
int		split_token_end_after_key(t_expander_var *var);

// expand_update_replace.c
int		replace_var(t_expander_var *var, char *new_value, int new_index);
int		check_for_simple_replace(t_expander_var *var, int j);
int		simple_replace(t_expander_var *var, char *new_value, int new_index);
int		replace_token_value(t_expander_var *var, int i);

// expand_update_concatenate.c
void	set_concatenate_bools(t_expander_var *var);
int		concatenate_end(t_expander_var *var, int i);
int		concatenate_begin(t_expander_var *var, int *i);

// expand_update_utils.c
void	*create_new_node(char *value);
void	insert_token_into_list(t_list *new_node, t_expander_var *var);
void	*free_split_value(char **split_value, int i);



void	remove_empty_tokens_from_list(t_list **list_start);
#endif