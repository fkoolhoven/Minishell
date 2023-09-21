/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:25:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/20 19:35:44 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
