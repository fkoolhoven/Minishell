/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:43:49 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 17:17:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	end_of_expandable_is_found(char c)
{
	if (c == '\0')
		return (true);
	else if (ft_isspace(c))
		return (true);
	else if (c == '?')
		return (true);
	else if (c == '$')
		return (true);
	else if (char_is_quote(c))
		return (true);
	return (false);
}

char	**add_quotes_to_strings(char **split_value)
{
	int	i;

	i = 0;
	while (split_value[i])
	{
		split_value[i] = ft_strjoin("\"", split_value[i]); // free stuff 
		split_value[i] = ft_strjoin(split_value[i], "\""); // free stuff
		printf("split_value[%i] = %s\n", i, split_value[i]);
		i++;
	}
	return (split_value);
}

int	expand_variable(t_list	**tokens, t_token *token, t_htable *env, int *i, bool concatenate_begin)
{
	bool	concatenate_end = false;
	char	*key;
	char	*new_value;
	int		exit_code;
	int		start;

	exit_code = EXIT_SUCCESS;
	start = *i;
	(*i)++;
	if (end_of_expandable_is_found(token->value[*i]))
		return (EXIT_SUCCESS);
	while (!end_of_expandable_is_found(token->value[*i]))
		(*i)++;
	if (!ft_isspace(!token->value[*i]))
		concatenate_end = true;
	key = ft_substr(token->value, start, *i - start);
	if (key == NULL)
		return (malloc_error_return_failure("expander"));
	new_value = find_env_value(env, key);
	free(key);
	if (!new_value)
		exit_code = VALUE_NOT_FOUND;

	char **split_value;
	printf("\n\nGOING TO SPLIT TOKEN VALUE, new_value = %s and current_token = %s\n\n", new_value, token->value);
	sleep(1);
	split_value = split_token_value(new_value, token->type);
	printf("after added quotes split value = = %s\n", split_value[0]);
	// check for errors
	// add quotes to all split_values
	if (ft_isspace(new_value[0]))
		concatenate_begin = false;
	if (ft_isspace(new_value[ft_strlen(new_value) - 1]))
		concatenate_end = false;
	add_quotes_to_strings(split_value);
	if (split_value != NULL)
	{
		printf("\n\nGOING TO UPDATE LIST\n\n");
		update_list(token, split_value, tokens, concatenate_begin, concatenate_end, start, *i - start, i);
	}
	if (start > 0 && exit_code != EXIT_FAILURE)
		*i = start - 1;
	return (exit_code);
}
