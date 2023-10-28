/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/28 19:12:01 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_split_value(char **split_value, int i)
{
	while (split_value[i])
	{
		free(split_value[i]);
		i++;
	}
	return (malloc_error_return_null("tokenizer split"));
}

static void	insert_token_into_list(t_list *new_node, t_expander_var *var)
{
	t_list	*temp;

	temp = var->tokens->next;
	var->tokens->next = new_node;
	new_node->next = temp;
}

void	*create_new_node(char **split_value, int i)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = initialize_token();
	if (new_token == NULL)
		return (free_split_value(split_value, i));
	new_token->type = WORD;
	new_token->value = split_value[i];
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free (new_token);
		return (free_split_value(split_value, i));
	}
	return (new_node);
}

void	*create_new_node_split(char *right)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = initialize_token();
	if (new_token == NULL)
		; // handle error
	new_token->type = WORD;
	new_token->value = right;
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free (new_token);
		; // handle error
	}
	return (new_node);
}

int	replace_var(t_expander_var *var, char *new_value)
{
	char	*new_str;
	int		end_len;
	int		new_str_len;

	end_len = ft_strlen(var->token->value) - var->key_start - var->key_len;
	new_str_len = var->key_start + ft_strlen(new_value) + end_len;
	if (new_str_len == 0)
	{
		free(var->token->value);
		var->token->value = NULL;
		return (EXIT_SUCCESS);
	}
	new_str = ft_calloc(new_str_len + 1, sizeof(char));
	if (new_str == NULL)
		return (malloc_error_return_failure("expander"));
	ft_strlcpy(new_str, var->token->value, var->key_start + 1);
	ft_strlcat(new_str, new_value, new_str_len + 1);
	ft_strlcat(new_str, var->token->value + var->key_start + var->key_len, new_str_len + 1);
	free(var->token->value);
	var->token->value = new_str;
	return (EXIT_SUCCESS);
}

int	split_token(t_expander_var *var)
{
	t_list	*new_node;
	char	*left;
	char	*right;
	int		right_len;

	right_len = ft_strlen(var->token->value) - var->key_start - var->key_len;
	if (right_len > 0)
	{
		printf("A\n");
		right = ft_substr(var->token->value, var->key_start + var->key_len, right_len); // free stuff and check for errorrs
		if (right == NULL)
			return (malloc_error_return_failure("expander"));
		new_node = create_new_node_split(right);
		if (new_node == NULL)
		{
			free(right);
			return (malloc_error_return_failure("expander"));
		}
		printf("right = %s\n", right);
		insert_token_into_list(new_node, var);
	}
	else
		var->concatenate_end = false;
	if (var->key_start >= 0)
	{
		if (var->key_start == 0)
		{
			printf("B\n");
			left = ft_substr(var->token->value, 0, var->key_len);
		}
		else
		{
			printf("C\n");
			left = ft_substr(var->token->value, 0, var->key_start);
		}
		if (left == NULL)
			return (malloc_error_return_failure("expander"));
		free(var->token->value);
		printf("left = %s\n", left);
		var->token->value = left;
	}
	else
		var->concatenate_begin = false;
	return (EXIT_SUCCESS);
}

int	update_list(t_expander_var *var)
{
	t_list	*new_node;
	int		i;

	i = 0;
	printf("bein bool = %i, end bool = %i\n", var->concatenate_begin, var->concatenate_end);
	if ((var->concatenate_begin && var->concatenate_end && !var->split_value[i + 1]) || ((size_t)var->key_len == ft_strlen(var->token->value) && !var->split_value[i + 1]))
	{
		printf("1\n");
		if (replace_var(var, var->split_value[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		var->index = var->key_start + ft_strlen(var->split_value[i] - 1); 
		return (EXIT_SUCCESS);
	}
	if (split_token(var) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((size_t)var->key_len == ft_strlen(var->token->value))
	{
		printf("2\n");
		var->token->value = var->split_value[i]; // free prev
		var->index = ft_strlen(var->split_value[i]) - 1;
		var->concatenate_begin = false;
		i++;
	}
	if (!var->split_value[i])
		return (EXIT_SUCCESS);
	if (var->concatenate_begin)
	{
		printf("3\n");
		var->token->value = ft_strjoin(var->token->value, var->split_value[i]); // free stuff and check for errors
		i++; 
		var->index = var->key_start + ft_strlen(var->split_value[i]) - 1;
		var->tokens = var->tokens->next;
		if (var->tokens)
			var->token = (t_token *)var->tokens->content;
		else
			return (EXIT_SUCCESS);
	}
	while (var->split_value[i])
	{
		printf("4\n");
		var->index = ft_strlen(var->split_value[i]) - 1;
		var->token = (t_token *)var->tokens->content;
		if (var->concatenate_end && !var->split_value[i + 1])
		{
			printf("5\n");
			var->tokens = var->tokens->next;
			var->token = (t_token *)var->tokens->content;
			var->token->value = ft_strjoin(var->split_value[i], var->token->value); // free prev and check for errors
			break ;
		}
		new_node = create_new_node(var->split_value, i);
		if (new_node == NULL)
			return (EXIT_FAILURE);
		insert_token_into_list(new_node, var);
		var->tokens = var->tokens->next;
		i++;
	}
	var->index = 0;
	free(var->split_value);
	return (EXIT_SUCCESS);
}
