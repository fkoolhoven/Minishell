/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_terminate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:48:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 15:28:51 by fkoolhov         ###   ########.fr       */
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
		// free(token->value);
		free(token);
		tokens = tokens->next;
	}
}
