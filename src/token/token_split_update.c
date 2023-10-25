/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/25 16:38:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_split_value(char **split_value, int i)
{
	while (split_value[i])
	{
		free(split_value[i]);
		i++;
	}
	return (malloc_error_return_failure("tokenizer split"));
}

static int	update_redirect_value(t_token *current_token, char **split_value)
{
	char	*new_value;
	char	*temp;
	int		i;

	i = 0;
	new_value = split_value[i];
	i++;
	while (split_value[i])
	{
		temp = new_value;
		new_value = ft_strjoin(new_value, " ");
		free(temp);
		if (new_value == NULL)
			return (free_split_value(split_value, i));
		temp = new_value;
		new_value = ft_strjoin(new_value, split_value[i]);
		free(temp);
		free(split_value[i]);
		if (new_value == NULL)
			return (free_split_value(split_value, i + 1));
		i++;
	}
	free(current_token->value);
	current_token->value = new_value;
	return (EXIT_SUCCESS);
}

static void	insert_token_into_list(t_list *new_node, t_list **tokens)
{
	t_list	*temp;

	temp = (*tokens)->next;
	(*tokens)->next = new_node;
	new_node->next = temp;
	*tokens = (*tokens)->next;
}

static int	insert_word_tokens(t_token *current_token, char **split_value,
	t_list *tokens)
{
	t_token	*new_token;
	t_list	*new_node;
	int		i;

	i = 0;
	free(current_token->value);
	current_token->value = split_value[i];
	i++;
	while (split_value[i])
	{
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
		insert_token_into_list(new_node, &tokens);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	update_list(t_token *current_token, char **split_value, t_list *tokens)
{
	int	error_check;

	if (current_token->type == WORD)
		error_check = insert_word_tokens(current_token, split_value, tokens);
	else
		error_check = update_redirect_value(current_token, split_value);
	free (split_value);
	return (error_check);
}
