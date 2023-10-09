/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:47:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 15:49:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_char_from_string(char *string, int index)
{
	char	*result;
	int		strlen;

	strlen = ft_strlen(string);
	result = ft_calloc(strlen, sizeof(char));
	if (result == NULL)
	{
		ft_putendl_fd("malloc error quotes", STDERR_FILENO);
		return (NULL);
	}
	ft_strlcpy(result, string, index + 1);
	ft_strlcpy(result + index, string + index + 1, strlen - index);
	free(string);
	return (result);
}

int	find_next_quote(char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] != quote && input[i])
		i++;
	return (i);
}

char	*get_new_value_without_quotes(char *old_value, int *i)
{
	char	*temp;
	char	*new_value;
	int		first_quote;

	first_quote = *i;
	*i = find_next_quote(old_value, *i);
	new_value = remove_char_from_string(old_value, first_quote);
	if (new_value == NULL)
		return (NULL);
	(*i)--;
	if (new_value[*i] == '\0')
		return (new_value);
	temp = remove_char_from_string(new_value, *i);
	if (temp == NULL)
	{
		free(new_value);
		return (NULL);
	}
	new_value = temp;
	(*i)--;
	return (new_value);
}

char	*remove_quotes_from_value(t_token *token)
{
	char	*value;
	int		i;

	value = token->value;
	i = 0;
	while (value[i])
	{
		if (char_is_quote(value[i]))
		{
			value = get_new_value_without_quotes(value, &i);
			if (value == NULL)
				return (NULL);
		}
		i++;
	}
	return (value);
}

int	remove_quotes(t_list **list_start)
{
	t_token	*current_token;
	t_list	*tokens;

	tokens = *list_start;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		current_token->value = remove_quotes_from_value(current_token);
		if (current_token->value == NULL)
		{
			terminate_token_list_error(list_start);
			return (EXIT_FAILURE);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
