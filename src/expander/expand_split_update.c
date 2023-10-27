/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 17:25:47 by fkoolhov         ###   ########.fr       */
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

static void	insert_token_into_list(t_list *new_node, t_list **tokens)
{
	t_list	*temp;

	temp = (*tokens)->next;
	(*tokens)->next = new_node;
	new_node->next = temp;
	*tokens = (*tokens)->next;
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
	new_token->was_expanded = true;
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free (new_token);
		return (free_split_value(split_value, i));
	}
	return (new_node);
}


static int	replace_var(t_token *token, char *new_value,
	int beginning_len, int rm_len)
{
	char	*new_str;
	int		end_len;
	int		new_str_len;

	printf("\n\nIN REPLACE VAR FUNC\n\n");
	end_len = ft_strlen(token->value) - beginning_len - rm_len;
	new_str_len = beginning_len + ft_strlen(new_value) + end_len;
	if (new_str_len == 0)
	{
		free(token->value);
		token->value = NULL;
		return (EXIT_SUCCESS);
	}
	new_str = ft_calloc(new_str_len + 1, sizeof(char));
	if (new_str == NULL)
		return (malloc_error_return_failure("expander"));
	ft_strlcpy(new_str, token->value, beginning_len + 1);
	ft_strlcat(new_str, new_value, new_str_len + 1);
	ft_strlcat(new_str, token->value + beginning_len + rm_len, new_str_len + 1);
	free(token->value);
	token->value = new_str;
	return (EXIT_SUCCESS);
}

int	get_amount_of_words(char **split_value)
{
	int i = 0;
	while (split_value[i])
		i++;
	return (i);
}

static void	insert_token_into_list_split(t_list *new_node, t_list **tokens)
{
	t_list	*temp;

	temp = (*tokens)->next;
	(*tokens)->next = new_node;
	new_node->next = temp;
	// *tokens = (*tokens)->next;
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
	new_token->was_expanded = true;
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free (new_token);
		; // handle error
	}
	return (new_node);
}

void	split_current_token(t_list **tokens, t_token *current_token, int left_len, int rm_len, bool *concatenate_begin, bool *concatenate_end)
{
	t_list	*new_node;
	char	*left;
	char	*right;
	int		right_len;

	right_len = ft_strlen(current_token->value) - left_len - rm_len;
	if (right_len > 0)
	{
		right = ft_substr(current_token->value, left_len + rm_len, right_len);
		printf("right = %s\n", right);
		new_node = create_new_node_split(right);
		insert_token_into_list_split(new_node, tokens);
		// *tokens = (*tokens)->next; // make sure to only concat to last if concat end, otherwise should insert at right token like "abc hello world zz" but also "abc hizz"
	}
	else
		*concatenate_end = false;
	if (left_len != 0)
	{
		left = ft_substr(current_token->value, 0, left_len);
		current_token->value = left; // free prev
		printf("left = %s\n", left);
	}
	else
		*concatenate_begin = false;
}

int	update_list(t_token *current_token, char **split_value, t_list **tokens, bool concatenate_begin, bool concatenate_end, int beginning_len, int rm_len, int *index)
{
	t_list	*new_node;
	int		error_check;
	int		i;

	error_check = EXIT_SUCCESS;
	i = 0;
	if ((concatenate_begin && concatenate_end && !split_value[i + 1]) || ((size_t)rm_len == ft_strlen(current_token->value) && !split_value[i + 1]))
	{
		printf("\n\nGOING TO REPLACE VAR 1\n");
		printf("second str = %s\n", split_value[i + 1]);
		printf("rm len = %zu and strlen = %zu\n", (size_t)rm_len, ft_strlen(current_token->value));
		replace_var(current_token, split_value[i], beginning_len, rm_len);
		*index = beginning_len + ft_strlen(split_value[i] - 1); 
		return (EXIT_SUCCESS);
	}
	split_current_token(tokens, current_token, beginning_len, rm_len, &concatenate_begin, &concatenate_end);
	if ((size_t)rm_len == ft_strlen(current_token->value))
	{
		current_token->value = split_value[i];
		i++;
	}
	while (split_value[i])
	{
		printf("\n\nIN SPLIT VALUE LOOP with %s\n\n", split_value[i]);
		*index = ft_strlen(split_value[i] - 1);
		current_token = (t_token *)(*tokens)->content;
		printf("current token value in split loop = %s\n", current_token->value);
		if (concatenate_end && !split_value[i] + 1)
		{
			printf("concatenate_end && !split_value[i] + 1\n");
			current_token->value = ft_strjoin(split_value[i], current_token->value); // free prev
			break ;
		}
		new_node = create_new_node(split_value, i);
		if (new_node == NULL)
			return (EXIT_FAILURE);
		insert_token_into_list(new_node, tokens);
		i++;
	}
	free (split_value);
	return (error_check);
}
