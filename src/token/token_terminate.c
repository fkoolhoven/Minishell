/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_terminate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:48:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 16:47:16 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate_token_list(t_list **list_start)
{
	t_token	*token;
	t_list	*tokens;
	t_list	*temp;

	tokens = *list_start;
	while (tokens)
	{
		printf("TERMINATING TOKEN\n");
		temp = tokens->next;
		token = (t_token *)tokens->content;
		free(token);
		free(tokens);
		tokens = temp;
	}
}

void	*terminate_token_list_error(t_list **list_start)
{
	t_token	*token;
	t_list	*tokens;
	t_list	*temp;

	tokens = *list_start;
	while (tokens)
	{
		printf("TERMINATING TOKEN ERROR\n");
		temp = tokens->next;
		token = (t_token *)tokens->content;
		if (token->value)
			free(token->value);
		free(token);
		free(tokens);
		tokens = temp;
	}
	return (NULL);
}
