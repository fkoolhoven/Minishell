/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:06:56 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/28 17:17:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_word_strl(char *str, int *i)
{
	int	start;

	while (ft_isspace(str[*i]))
		(*i)++;
	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
	{
		if (char_is_quote(str[*i]))
			*i = find_next_quote(str, *i);
		if (str[*i])
			(*i)++;
	}
	return (*i - start);
}

static int	calculate_nbr_of_strings(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		nbr++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (char_is_quote(str[i]))
				i = find_next_quote(str, i);
			if (str[i])
				i++;
		}
	}
	return (nbr);
}

static char	**split_string_into_words(char *str, int nbr_of_strings,
	char **split_value)
{
	int		i;
	int		strl;
	int		j;

	i = 0;
	j = 0;
	strl = 0;
	while (j < nbr_of_strings)
	{
		strl = calculate_word_strl(str, &i);
		split_value[j] = (char *)malloc(sizeof(char) * strl + 1);
		if (split_value[j] == NULL)
		{
			ft_free_str_array(split_value);
			return (malloc_error_return_null("tokenizer split"));
		}
		ft_strlcpy(split_value[j], &str[i - strl], strl + 1);
		j++;
	}
	split_value[j] = NULL;
	return (split_value);
}

char	**split_token_value(char *str, int type)
{
	char	**split_value;
	int		nbr_of_strings;

	nbr_of_strings = calculate_nbr_of_strings(str);
	if (type != WORD && nbr_of_strings > 1)
	{
		return (NULL); // handle error
	}
	split_value = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (split_value == NULL)
	{
		return (NULL); // handle error
	}
	split_value = split_string_into_words(str, nbr_of_strings, split_value);
	if (split_value == NULL)
		return (NULL); // handle error
	return (split_value);
}
