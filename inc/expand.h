/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:32 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 16:53:32 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

// expand.c
int	expand(t_list **list_start, t_htable *env);

// expand_variable.c
int	expand_variable(t_token *token, t_htable *env, int *i);

#endif