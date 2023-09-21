/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:35:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 19:39:04 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// too many functions in file

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

bool	next_token_is_found(char *input, int i)
{
	if (char_is_operator(input[i]))
		return (true);
	else if (char_is_quote(input[i]))
		return (true);
	return (false);
}

bool	found_expandable(char *input, int i)
{
	if (input[i] == '$' && input[i + 1] != ' ' && input[i + 1])
		return (true);
	else
		return (false);
}

bool	token_contains_expandable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (found_expandable(str, i))
			return (true);
		i++;
	}
	return (false);
}
