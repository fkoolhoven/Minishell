/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:47:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/05 17:46:02 by fkoolhov         ###   ########.fr       */
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

char	*remove_quotes_from_value(t_token *token)
{
	char	*old_value;
	char	*new_value;
	int		first_quote;
	int		second_quote;
	int		i;

	old_value = token->value;
	new_value = old_value;
	i = 0;
	while (old_value[i])
	{
		if (char_is_quote(old_value[i]))
		{
			first_quote = i;
			i = find_next_quote(old_value, i);
			new_value = remove_char_from_string(old_value, first_quote);
			if (new_value == NULL)
				return (NULL);
			i--;
			if (new_value[i] == '\0')
				break ;
			second_quote = i;
			new_value = remove_char_from_string(new_value, second_quote);
			if (new_value == NULL)
				return (NULL);
			i--;
			old_value = new_value;
		}
		i++;
	}
	return (new_value);
}

int	remove_quotes(t_list **list_start)
{
	t_token	*current_token;
	t_list	*tokens;
	char	*new_value;

	tokens = *list_start;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		new_value = remove_quotes_from_value(current_token);
		if (new_value == NULL)
		{
			terminate_token_list_error(list_start);
			return (EXIT_FAILURE);
		}
		current_token->value = new_value;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
