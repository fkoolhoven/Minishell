/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 12:45:48 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SIMPLE IMPLEMENTATION OF INTERFACE
   Things to change in future:
   			- better exit function which frees everything
			- make sure it gives correct exit status
			- ...

*/

// ctrl-C displays a new prompt on a new line.
// ctrl-D exits the shell.
// ctrl-\ does nothing.

// void	check_leaks(void)
// {
// 	system("leaks -q minishell");
// }

int	main(void)
{
	char			*user_input;
	t_list			*tokens;
	t_hash_table	*env;

	// atexit(check_leaks);
	tokens = NULL;
	env = init_env();
	st_print_hashtable(env);

	while (1)
	{
		signal(SIGINT, &catch_signals);
		signal(SIGQUIT, SIG_IGN);
		user_input = readline("--> ");
		if (!(user_input))
		{
			printf("Exiting shell...\n");
			exit(EXIT_SUCCESS);
		}
		else if (ft_strnstr(user_input, "exit", ft_strlen(user_input)) != NULL)
		{
			free(user_input);
			printf("Exiting ...\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			tokens = tokenize_input(user_input);
			print_tokens(tokens); // function for testing / checks
			expand_parameters(&tokens, env);
			add_history(user_input);
			free(user_input);
		}
	}
	terminate_hashtable(env);
	return (0);
}
