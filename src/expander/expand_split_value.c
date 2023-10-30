/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:06:56 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 19:45:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_quotes_to_strings(char **split_value)
{
	char	*temp;
	int		i;

	i = 0;
	while (split_value[i])
	{
		temp = split_value[i];
		split_value[i] = ft_strjoin("\"", split_value[i]);
		free(temp);
		if (split_value[i] == NULL)
			return (free_split_value(split_value, i));
		temp = split_value[i];
		split_value[i] = ft_strjoin(split_value[i], "\"");
		free(temp);
		if (split_value[i] == NULL)
			return (free_split_value(split_value, i));
		i++;
	}
	return (split_value);
}

static int	calculate_word_strl(char *str, int *i)
{
	int	start;

	while (ft_isspace(str[*i]))
		(*i)++;
	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
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
			i++;
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

int	split_token_value(t_expander_var *var)
{
	int		nbr_of_strings;

	nbr_of_strings = calculate_nbr_of_strings(var->new_value);
	if (var->token->type != WORD && nbr_of_strings > 1)
		return (minishell_error_return_failure("ambiguous redirect"));
	var->split_value = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (var->split_value == NULL)
		return (malloc_error_return_failure("expander"));
	var->split_value = split_string_into_words(var->new_value,
			nbr_of_strings, var->split_value);
	if (var->split_value == NULL)
		return (EXIT_FAILURE);
	var->split_value = add_quotes_to_strings(var->split_value);
	if (var->split_value == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
