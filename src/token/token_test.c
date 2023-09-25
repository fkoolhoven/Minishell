/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:58:44 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 11:59:37 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ONLY TEST FUNCTIONS

void	print_tokens(t_list *tokens)
{
	t_token	*current_token;

	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		printf("TOKEN type = %i\n", current_token->type);
		printf("TOKEN value = %s\n", current_token->value);
		printf("TOKEN expand = %i\n", current_token->expand);
		printf("\n");
		tokens = tokens->next;
	}
}
