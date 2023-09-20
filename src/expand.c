/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 18:16:29 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expand_variable(t_token *token)
{
    int i;

    i = 0;
    while (token->value[i])
    {
        if (token->value[i] == '$')
        {
            // expand based on env list? could be t_list of env variables?
        }
        i++;
    }
}

void    expand_parameters(t_list **tokens)
{
    int         parser_check;
	t_token 	*current_token;
    t_list      *list_start = *tokens;

	while (*tokens)
	{
		current_token = (t_token *)(*tokens)->content;
        if (current_token->expand == true)
            expand_variable(current_token);
		*tokens = (*tokens)->next;
	}
    parser_check = parse_tokens(list_start);
    if (parser_check != EXIT_SUCCESS)
        return ;
}
