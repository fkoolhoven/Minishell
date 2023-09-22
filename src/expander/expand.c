/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 14:47:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free everything to prevent mem leaks!
// Replaces the expandable (for example $var) with the associated value form
// the env hashtable
void	replace_var(t_token *token, char *var, int start, int rm_strlen)
{
	char	*beginning;
	char	*end;
	char	*new_string;
	int		end_strlen;

	beginning = ft_substr(token->value, 0, start);
	end_strlen = ft_strlen(token->value) - start - rm_strlen;
	end = ft_substr(token->value, start + rm_strlen, end_strlen);
	new_string = ft_strjoin(beginning, var);
	new_string = ft_strjoin(new_string, end);
	// free(beginning);
	// free(var);
	// free(end);
	free(token->value);
	token->value = new_string;
}

// free substring in this func
// Goes through the value (char *) of the token and finds all the expandables
void	expand_variable(t_token *token, t_htable *env)
{
	int		i;
	int		start;
	char	*var;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			start = i;
			i++;
			while (token->value[i] && !ft_isspace(token->value[i]) && token->value[i] != '$')
				i++;
			var = ft_substr(token->value, start, i - start);
			var = find_env_value(env, var);
			replace_var(token, var, start, i - start);
			i = start - 1;
		}
		i++;
	}
}

// Goes through the list of tokens and sees which tokens contain an expandable
void	expand_parameters(t_list **tokens, t_htable *env)
{
	int		parser_check;
	t_token	*current_token;
	t_list	*list_start;

	list_start = *tokens;
	while (*tokens)
	{
		current_token = (t_token *)(*tokens)->content;
		if (current_token->expand == true)
			expand_variable(current_token, env);
		*tokens = (*tokens)->next;
	}
	parser_check = parse_tokens(list_start);
	if (parser_check != EXIT_SUCCESS)
		return ;
}
