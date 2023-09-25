/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_terminate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:48:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 15:17:44 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate_token_list(t_list **list_start)
{
	t_token	*token;
	t_list	*tokens;

	tokens = *list_start;
	while (tokens)
	{
		printf("TERMINATING TOKEN\n");
		token = (t_token *)tokens->content;
		printf("1, value = %s, loc = %p\n", token->value, &token->value);
		if (token->value)
		{
			printf("1.5\n");
			free(token->value);
		}
		printf("2\n");
		free(token);
		printf("3\n");
		tokens = tokens->next;
		printf("4\n");
	}
}
