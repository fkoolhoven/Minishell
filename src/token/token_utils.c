/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:35:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/11 18:03:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_quote(char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] != quote && input[i])
		i++;
	return (i);
}

bool	char_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

bool	end_of_value(char c)
{
	if (ft_isspace(c))
		return (true);
	else if (char_is_operator(c))
		return (true);
	else if (c == '\0')
		return (true);
	return (false);
}

int	calculate_strlen_for_token_value(char *input, int *i)
{
	int		strlen;
	int		end_quote;

	strlen = 0;
	while (!end_of_value(input[*i]))
	{
		if (char_is_quote(input[*i]))
		{
			end_quote = find_next_quote(input, *i);
			strlen += end_quote - *i;
			*i = end_quote;
			if (!input[*i])
				break ;
		}
		(*i)++;
		strlen++;
	}
	return (strlen);
}
