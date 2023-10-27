/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:19:53 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 17:20:14 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// token_expand.c
int		expand_tokens(t_list **list_start, t_htable *env);

// token_expand_variable.c
int		expand_variable(t_list	**tokens, t_token *token, t_htable *env, int *i, bool concatenate_begin);

// token_split.c
char	**split_token_value(char *str, int type);

// token_split_update.c
int		update_list(t_token *current_token, char **split_value, t_list **tokens, bool concatenate_begin, bool concatenate_end, int beginning_len, int rm_len, int *i);

#endif