/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:56:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/30 19:11:45 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_token_beginning_before_key(t_expander_var *var)
{
	char	*left;

	if (var->key_start >= 0)
	{
		if (var->key_start == 0)
			left = ft_substr(var->token->value, 0, var->key_len);
		else
			left = ft_substr(var->token->value, 0, var->key_start);
		if (left == NULL)
			return (malloc_error_return_failure("expander"));
		free(var->token->value);
		var->token->value = left;
		var->token->expansion_beginning = true;
	}
	else
		var->concatenate_begin = false;
	return (EXIT_SUCCESS);
}

static t_list	*get_new_token_for_split(t_expander_var *var, int right_len)
{
	t_token	*new_token;
	t_list	*new_node;
	int		right_start;
	char	*right;

	right_start = var->key_start + var->key_len;
	right = ft_substr(var->token->value, right_start, right_len);
	if (right == NULL)
		return (malloc_error_return_null("expander"));
	new_node = create_new_node(right);
	if (new_node == NULL)
	{
		free(right);
		return (malloc_error_return_null("expander"));
	}
	new_token = (t_token *)new_node->content;
	new_token->expansion_end = true;
	return (new_node);
}

int	split_token_end_after_key(t_expander_var *var)
{
	t_list	*new_node;
	int		right_len;

	right_len = ft_strlen(var->token->value) - var->key_start - var->key_len;
	if (right_len > 0)
	{
		if (var->token->type != WORD)
			return (minishell_error_return_failure("ambiguous redirect"));
		new_node = get_new_token_for_split(var, right_len);
		if (new_node == NULL)
			return (EXIT_FAILURE);
		insert_token_into_list(new_node, var);
		var->token_was_split = true;
	}
	else
	{
		var->token_was_split = false;
		var->concatenate_end = false;
	}
	return (EXIT_SUCCESS);
}
