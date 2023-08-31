/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:35:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/31 16:35:54 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	char_is_single_quote(char c)
{
	if (c == '\'')
		return (true);
	else
		return (false);
}

bool	char_is_double_quote(char c)
{
	if (c == '\"')
		return (true);
	else
		return (false);
}

bool	char_is_quote(char c)
{
	if (char_is_single_quote(c) || char_is_double_quote(c))
		return (true);
	else
		return (false);
}

bool	char_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}