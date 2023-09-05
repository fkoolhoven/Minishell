/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:59:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/05 16:20:39 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_string_array(char **str_array)
{
	printf("GOING TO PRINT STRING ARRAY\n");
	int	i;

	i = 0;
	while (str_array[i])
	{
		printf("%s\n", str_array[i]);
		i++;
	}
}

void	print_command_list(t_command *list)
{
	printf("GOING TO PRINT COMMAND LIST\n");
	while (list)
	{
		print_string_array(list->command);
		printf("\n");
		list = list->next;
	}
}

size_t	calculate_amount_of_word(t_list *tokens)
{
	size_t	amount_of_words;
	t_token *current_token;

	amount_of_words = 0;
	current_token = (t_token *)tokens->content;
	while (tokens && current_token->type == WORD)
	{
		current_token = (t_token *)tokens->content;
		amount_of_words++;
		tokens = tokens->next;
	}
		printf("amount of words = %zu\n", amount_of_words);
	return (amount_of_words);
}

void	parse_tokens(t_list *tokens)
{
	t_command	*command_list;
	t_command	*new_command;
	t_token 	*current_token;
	size_t		amount_of_words;
	char		**command;
	// char 		*command[] = {"command", "arg1", "arg2", NULL};
	
	// command_list = lstnew_command(command, NULL, NULL);
	command_list = NULL;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		printf("in parser value = %s\n", current_token->value);


		amount_of_words = calculate_amount_of_word(tokens);
		command = ft_calloc(amount_of_words + 1, sizeof(char *));
		int	i = 0;
		while (current_token->type == WORD)
		{
			current_token = (t_token *)tokens->content;
			command[i] = current_token->value; // malloc?
			printf("command [%i] = %s\n", i, command[i]);
			tokens = tokens->next;
			i++;
		}
		
		if (!command_list)
		{
			command_list = lstnew_command(command, NULL, NULL);
		}
		else
		{
			new_command = lstnew_command(command, NULL, NULL);
			lstadd_back_command(&command_list, new_command);
		}
		
		while (current_token->type != WORD)
		{
			current_token = (t_token *)tokens->content;
			tokens = tokens->next;
		}
		printf("END OF LOOP\n");
	}
	print_command_list(command_list);
}