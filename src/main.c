/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/22 14:32:51 by fkoolhov         ###   ########.fr       */
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

int	main(int argc, char **envp)
{
	char		*user_input;
	t_list		*tokens;
	t_htable	*env;

	// atexit(check_leaks);
	tokens = NULL;
	env = init_env(envp);
	print_hashtable(env);
	argc = 0;
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
			printf("here0\n");
			print_tokens(tokens); // function for testing / checks
			printf("here1\n");
			expand_parameters(&tokens, env);
			printf("here2\n");
			add_history(user_input);
			free(user_input);
		}
	}
	terminate_hashtable(env);
	return (0);
}
