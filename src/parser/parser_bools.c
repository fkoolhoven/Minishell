/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type_bools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:25:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/11 17:52:35 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	char_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (true);
	else
		return (false);
}

bool	token_is_input_type(t_token *token)
{
	if (token->type == INFILE || token->type == HEREDOC)
		return (true);
	return (false);
}

bool	token_is_output_type(t_token *token)
{
	if (token->type == OUTFILE || token->type == OUTFILE_APPEND)
		return (true);
	return (false);
}
