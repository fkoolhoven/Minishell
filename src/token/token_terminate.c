/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_terminate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:48:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/25 15:26:24 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate_token(t_list *token)
{
	t_token	*to_delete;

	to_delete = (t_token *)token->content;
	if (to_delete->value)
		free(to_delete->value);
	free(to_delete);
	free(token);
}

void	terminate_token_list_error(t_list **list_start)
{
	t_list	*tokens;
	t_list	*temp;

	tokens = *list_start;
	while (tokens)
	{
		temp = tokens->next;
		terminate_token(tokens);
		tokens = temp;
	}
}

void	*terminate_token_list_error_null(t_list **list_start)
{
	terminate_token_list_error(list_start);
	return (NULL);
}

int	terminate_token_list_error_failure(t_list **list_start)
{
	terminate_token_list_error(list_start);
	return (EXIT_FAILURE);
}

void	terminate_token_list(t_list **list_start)
{
	t_token	*token;
	t_list	*tokens;
	t_list	*temp;

	tokens = *list_start;
	while (tokens)
	{
		temp = tokens->next;
		token = (t_token *)tokens->content;
		free(token);
		free(tokens);
		tokens = temp;
	}
}
