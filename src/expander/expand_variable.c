/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:43:49 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 16:54:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Replaces the old variable (for example $USER) with new_value (for example
// fkoolhov) from the env
int	replace_var(t_token *token, char *new_value, int beginning_len, int rm_len)
{
	char	*new_str;
	int		end_len;
	int		new_str_len;

	end_len = ft_strlen(token->value) - beginning_len - rm_len;
	new_str_len = beginning_len + ft_strlen(new_value) + end_len;
	new_str = ft_calloc(new_str_len + 1, sizeof(char));
	if (new_str == NULL)
	{
		ft_putendl_fd("minishell: malloc error expander", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_strlcpy(new_str, token->value, beginning_len + 1);
	ft_strlcat(new_str, new_value, new_str_len + 1);
	ft_strlcat(new_str, token->value + beginning_len + rm_len, new_str_len + 1);
	free(token->value);
	token->value = new_str;
	return (EXIT_SUCCESS);
}

bool	end_of_expandable_is_found(char c)
{
	if (c == '\0')
		return (true);
	else if (ft_isspace(c))
		return (true);
	else if (c == '$')
		return (true);
	else if (char_is_quote(c))
		return (true);
	return (false);
}

// Gets the new value from the env list and hands it to replace_var
// that will replace old with new value;
int	expand_variable(t_token *token, t_htable *env, int *i)
{
	char	*key;
	char	*new_value;
	int		start;

	start = *i;
	(*i)++;
	while (!end_of_expandable_is_found(token->value[*i]))
		(*i)++;
	key = ft_substr(token->value, start, *i - start);
	if (key == NULL)
	{
		ft_putendl_fd("minishell: malloc error expander key", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	new_value = find_env_value(env, key);
	free(key);
	if (replace_var(token, new_value, start, *i - start) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*i = start - 1;
	return (EXIT_SUCCESS);
}