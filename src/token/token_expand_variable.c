/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:43:49 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:06 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_var(t_token *token, char *new_value,
	int beginning_len, int rm_len)
{
	char	*new_str;
	int		end_len;
	int		new_str_len;

	end_len = ft_strlen(token->value) - beginning_len - rm_len;
	new_str_len = beginning_len + ft_strlen(new_value) + end_len;
	if (new_str_len == 0)
	{
		free(token->value);
		token->value = NULL;
		return (EXIT_SUCCESS);
	}
	new_str = ft_calloc(new_str_len + 1, sizeof(char));
	if (new_str == NULL)
		return (malloc_error_return_failure("expander"));
	ft_strlcpy(new_str, token->value, beginning_len + 1);
	ft_strlcat(new_str, new_value, new_str_len + 1);
	ft_strlcat(new_str, token->value + beginning_len + rm_len, new_str_len + 1);
	free(token->value);
	token->value = new_str;
	return (EXIT_SUCCESS);
}

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

int	expand_variable(t_token *token, t_htable *env, int *i)
{
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
	key = ft_substr(token->value, start, *i - start);
	if (key == NULL)
		return (malloc_error_return_failure("expander"));
	new_value = find_env_value(env, key);
	free(key);
	if (!new_value)
		exit_code = VALUE_NOT_FOUND;
	if (replace_var(token, new_value, start, *i - start) == EXIT_FAILURE)
		exit_code = EXIT_FAILURE;
	if (start > 0 && exit_code != EXIT_FAILURE)
		*i = start - 1;
	return (exit_code);
}
