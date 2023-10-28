/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:19:53 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/28 18:26:13 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// token_expand.c
int		expand_tokens(t_list **list_start, t_htable *env);

// token_expand_variable.c
int		expand_variable(t_expander_var *var, t_htable *env);

// expand_split_value.c
char	**split_token_value(char *str, int type);

// token_split_update.c
int		update_list(t_expander_var *var);
int		replace_var(t_expander_var *var, char *new_value);

#endif