/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:47:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 16:50:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_char_from_string(char *string, int index)
{
	char	*result;
	int		strlen;

	strlen = ft_strlen(string);
	result = ft_calloc(strlen, sizeof(char));
	if (result == NULL)
	{
		free(string);
		return (malloc_error_return_null("tokenizer"));
	}
	ft_strlcpy(result, string, index + 1);
	ft_strlcpy(result + index, string + index + 1, strlen - index);
	free(string);
	return (result);
}

static int	delete_quotes(t_token *token, int first_quote, int *i)
{
	int		second_quote;
	char	*temp;
	char	*new_value;

	new_value = delete_char_from_string(token->value, first_quote);
	if (new_value == NULL)
		return (EXIT_FAILURE);
	(*i)--;
	second_quote = *i;
	temp = delete_char_from_string(new_value, second_quote);
	if (temp == NULL)
	{
		free(new_value);
		return (EXIT_FAILURE);
	}
	new_value = temp;
	(*i)--;
	token->value = new_value;
	return (EXIT_SUCCESS);
}

static int	find_and_delete_quotes(t_list **tokens, t_token **token, int *i, int *exit_code)
{
	int		first_quote;

	first_quote = *i;
	*i = find_next_quote((*token)->value, *i);
	printf("token value = %s, beginning = %i and end = %i\n", (*token)->value, (*token)->expansion_beginning, (*token)->expansion_end);
	if (!(*token)->value[*i])
	{
		if ((*token)->expansion_beginning == true)
		{
			printf("A token value = %s\n", (*token)->value);
			if (search_in_expanded_tokens(tokens, token, first_quote, i) == EXIT_FAILURE)
				return (EXIT_FAILURE); // set exitcode if syntax
			return (EXIT_SUCCESS);
		}
		else
		{
			printf("B with token value = %s\n", (*token)->value);
			// free(token->value);
			return (syntax_error_return_failure("unclosed quote", exit_code));
		}
	}
	if (delete_quotes(*token, first_quote, i) == EXIT_FAILURE)
	{
		printf("C\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	get_new_value(t_list **tokens, t_token *token, int *exit_code)
{
	int		i;

	i = 0;
	while (token->value[i])
	{
		if (char_is_quote(token->value[i]))
		{
			if (find_and_delete_quotes(tokens, &token, &i, exit_code) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	remove_quotes_from_tokens(t_list **list_start, int *exit_code)
{
	t_token	*current_token;
	t_list	*tokens;

	tokens = *list_start;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		if (get_new_value(&tokens, current_token, exit_code) == EXIT_FAILURE)
			return (terminate_token_list_error_failure(list_start));
		if (tokens)
			tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
