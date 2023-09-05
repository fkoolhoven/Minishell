/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:59:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/05 18:26:31 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print function for testing purposes
void	print_redirections(t_redirect *lst)
{
	while (lst)
	{
		printf("type = %i, value = %s\n", lst->type, lst->value);
		lst = lst->next;
	}
}

// print function for testing purposes
void	print_string_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		printf("%s ", str_array[i]);
		i++;
	}
}

// print function for testing purposes
void	print_command_list(t_command *list)
{
	while (list)
	{
		printf("\nINPUTS:\n");
		print_redirections(list->in);
		printf("\nCOMMAND + ARGS:\n");
		print_string_array(list->command);
		printf("\n\nOUTPUTS:\n");
		print_redirections(list->out);
		list = list->next;
	}
}

// Calculates amount of words in a sequence of tokens to calculate how much space is needed for char **command
size_t	calculate_amount_of_words(t_list *tokens)
{
	size_t	amount_of_words;
	t_token *current_token;

	amount_of_words = 0;
	if (tokens)
		current_token = (t_token *)tokens->content;
	while (tokens && current_token->type == WORD)
	{
		amount_of_words++;
		tokens = tokens->next;
		if (tokens)
			current_token = (t_token *)tokens->content;
	}
	// printf("amount of words = %zu\n", amount_of_words);
	return (amount_of_words);
}

// Adds new command struct (node) to command list
void	add_command_to_list(t_command **command_list, char **command, t_redirect *in, t_redirect *out)
{
	t_command	*new_command;

	// printf("\n\nADDIND NEW COMMAND TO LIST\n\n");
	if (!*command_list)
	{
		*command_list = lstnew_command(command, in, out);
		if (*command_list == NULL)
		{
			printf("Error allocating for command_list\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_command = lstnew_command(command, in, out);
		if (new_command == NULL)
		{
			printf("Error allocating for new_command\n");
			exit(EXIT_FAILURE);
		}
		lstadd_back_command(command_list, new_command);
	}
}

// Adds new redirect struct (node) to redirect list for a certain command
void	add_redirect_to_list(t_redirect **redirect_list, int type, char *value)
{
	t_redirect	*new_redirect;

	if (!*redirect_list)
	{
		*redirect_list = lstnew_redirect(type, value);
		if (*redirect_list == NULL)
		{
			printf("Error allocating for redirect_list\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_redirect = lstnew_redirect(type, value);
		if (new_redirect == NULL)
		{
			printf("Error allocating for new_redirect\n");
			exit(EXIT_FAILURE);
		}
		lstadd_back_redirect(redirect_list, new_redirect);
	}
}

// Goes through every token and adds it to linked list of input redirects, output redirects, or char **command
// Then combines all three in linked list of command structs
void	parse_tokens(t_list *tokens)
{
	t_command	*command_list;
	t_token 	*current_token;
	size_t		amount_of_words;
	t_redirect	*temp_lst;
	t_redirect	*in;
	t_redirect	*out;
	size_t		i;
	char		**command;

	temp_lst = NULL;
	in = NULL;
	out = NULL;
	command_list = NULL;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		// printf("in parser value = %s\n", current_token->value);
		while (tokens && token_is_input_type(current_token)) // parse input redirections
		{
			add_redirect_to_list(&temp_lst, current_token->type, current_token->value);
			tokens = tokens->next;
			if (tokens)
				current_token = (t_token *)tokens->content;
		}
		in = temp_lst;
		temp_lst = NULL;
		amount_of_words = calculate_amount_of_words(tokens);
		command = ft_calloc(amount_of_words + 1, sizeof(char *));
		i = 0;
		while (i < amount_of_words) // parse words (for char **command)
		{
			command[i] = current_token->value;
			tokens = tokens->next;
			if (tokens)
				current_token = (t_token *)tokens->content;
			i++;
		}
		while (tokens && token_is_output_type(current_token)) // parse output redirections
		{
			add_redirect_to_list(&temp_lst, current_token->type, current_token->value);
			tokens = tokens->next;
			if (tokens)
				current_token = (t_token *)tokens->content;
		}
		out = temp_lst;
		temp_lst = NULL;
		add_command_to_list(&command_list, command, in, out);
	}
	print_command_list(command_list);
}
