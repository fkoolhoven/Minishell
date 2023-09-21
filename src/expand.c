/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:47:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/21 19:35:55 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free everything to prevent mem leaks!
void	replace_var_with_value(t_token *token, char *var, int start, int rm_strlen)
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
	token->value = new_string;
}

char	*find_value_in_hashtable(char *key, t_hash_table *env)
{
	t_hash_node *node;

	// write function to search value based on key in hash table
	node = env->array[4];
	free(key);
	return (node->value);
}

void	expand_variable(t_token *token, t_hash_table *env)
{
	int		i;
	int		start;
	char	*var;

	i = 0;
	while (token->value[i]) // start over after one is replaced
	{
		if (token->value[i] == '$')
		{
			start = i;
			while (token->value[i] && !ft_isspace(token->value[i]))
				i++;
			var = ft_substr(token->value, start, i - start); // don't forget to free!
			printf("variable found = %s\n", var); // this would be the key to the content in env list
			var = find_value_in_hashtable(var, env);
			replace_var_with_value(token, var, start, i - start);
		}
		i++;
	}
}

void	expand_parameters(t_list **tokens, t_hash_table *env)
{
	int		parser_check;
	t_token	*current_token;
	t_list	*list_start = *tokens;

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
