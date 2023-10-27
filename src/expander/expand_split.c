/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:06:56 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 16:46:51 by fkoolhov         ###   ########.fr       */
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
	printf("NBR OF STRS = %i\n", nbr_of_strings);
	if (type != WORD && nbr_of_strings > 1)
	{
		return (NULL);
	}
	split_value = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (split_value == NULL)
	{
		return (NULL);
	}
	split_value = split_string_into_words(str, nbr_of_strings, split_value);
	if (split_value == NULL)
		return (NULL);
	return (split_value);
}

// char	**split_token_value(char *str, int type, int *exit_code)
// {
// 	char	**split_value;
// 	int		nbr_of_strings;

// 	nbr_of_strings = calculate_nbr_of_strings(str);
// 	if (type != WORD && nbr_of_strings > 1)
// 	{
// 		return (minishell_error_return_null("ambiguous redirect",
// 				exit_code, EXIT_FAILURE));
// 	}
// 	split_value = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
// 	if (split_value == NULL)
// 	{
// 		*exit_code = EXIT_FAILURE;
// 		return (malloc_error_return_null("tokenizer split"));
// 	}
// 	split_value = split_string_into_words(str, nbr_of_strings, split_value);
// 	if (split_value == NULL)
// 		*exit_code = EXIT_FAILURE;
// 	return (split_value);
// }

// After expanding an environment value, a token's value might be
// multiple strings. They need to be split up into seperate word tokens
// and inserted into the token list. In case of the token's type being
// a redirect type, the part of the token's value that is the result of
// the expansion needs to be trimmed of spaces.
// int	split_tokens(t_list **list_start, int *exit_code)
// {
// 	t_token	*token;
// 	t_list	*tokens;
// 	char	**split_value;

// 	*exit_code = EXIT_SUCCESS;
// 	tokens = *list_start;
// 	while (tokens)
// 	{
// 		token = (t_token *)tokens->content;
// 		if (token->was_expanded)
// 		{
// 			split_value = split_token_value(token->value, token->type, exit_code);
// 			if (split_value == NULL && *exit_code == EXIT_FAILURE)
// 				return (terminate_token_list_error_failure(list_start));
// 			else if (split_value != NULL)
// 			{
// 				*exit_code = update_list(token, split_value, tokens);
// 				if (*exit_code != EXIT_SUCCESS)
// 					return (terminate_token_list_error_failure(list_start));
// 			}
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (EXIT_SUCCESS);
// }
