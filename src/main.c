/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 15:02:11 by fkoolhov         ###   ########.fr       */
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
// should clear buffer after signal

int	main(int argc, char **argv, char **envp)
{
	char		*user_input;
	t_list		*tokens;
	t_htable	*env;

	tokens = NULL;
	env = init_env(envp);
	//print_hashtable(env);
	argc = 0;
	argv = NULL;
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
			if (tokens == NULL)
				ft_putendl_fd("Error\n", STDERR_FILENO);
			print_tokens(tokens);
			expand_parameters(&tokens, env);
			add_history(user_input);
			free(user_input);
		}
	}
	terminate_hashtable(env);
	return (0);
}
