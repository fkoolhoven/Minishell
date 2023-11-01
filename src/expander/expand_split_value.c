/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:06:56 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/01 10:55:23 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_quotes_to_strings(t_expander_var *var)
{
	char	*temp;
	int		i;

	i = 0;
	while (var->split_value[i])
	{
		temp = ft_strjoin("\"", var->split_value[i]);
		if (temp == NULL)
		{
			ft_free_str_array(var->split_value);
			return (malloc_error_return_failure("expander"));
		}
		free(var->split_value[i]);
		var->split_value[i] = temp;
		temp = ft_strjoin(var->split_value[i], "\"");
		if (temp == NULL)
		{
			ft_free_str_array(var->split_value);
			return (malloc_error_return_failure("expander"));
		}
		free(var->split_value[i]);
		var->split_value[i] = temp;
		i++;
	}
	return (EXIT_SUCCESS);
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
			return (malloc_error_return_null("expander"));
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
	if (add_quotes_to_strings(var) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (var->split_value == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
