/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes_expanded.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:58:13 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 17:00:25 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_both_quotes_expanded(t_token *starting_token, t_token *current_token, int first_quote, int second_quote, t_list **tokens)
{
	char	*temp;
	char	*new_value_first;
	char	*new_value_second;

	new_value_first = delete_char_from_string(starting_token->value, first_quote);
	if (new_value_first == NULL)
		return (EXIT_FAILURE);
	temp = delete_char_from_string(current_token->value, second_quote);
	if (temp == NULL)
	{
		free(new_value_first);
		return (EXIT_FAILURE);
	}
	starting_token->value = new_value_first;
	new_value_second = temp;
	printf("new value second = %s\n", new_value_second);
	current_token->value = new_value_second;
	if (ft_strlen(current_token->value) == 0)
		remove_empty_tokens_from_list(tokens);
	return (EXIT_SUCCESS);
}

int	search_in_expanded_tokens(t_list **tokens, t_token **starting_token, int first_quote, int *i)
{
	t_list	*search;
	t_token	*current_token;
	int		second_quote;

	search = (*tokens)->next;
	while (search)
	{
		current_token = (t_token *)search->content;
		second_quote = find_next_quote_expanded(current_token->value, 0, (*starting_token)->value[first_quote]);
		if (!current_token->value[second_quote] && current_token->expansion_end)
			return (EXIT_FAILURE);
		else if (current_token->value[second_quote])
		{
			if (delete_both_quotes_expanded(*starting_token, current_token, first_quote, second_quote, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			*tokens = search;
			*starting_token = (t_token *)search->content;
			*i = second_quote - 1;
			return (EXIT_SUCCESS);
		}
		search = search->next;
	}
	return (EXIT_FAILURE);
}
