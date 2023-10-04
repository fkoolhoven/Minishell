/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/04 13:03:09 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_and_exec(t_htable *env, char *user_input, int *exit_code)
{
	t_command	*command_list;
	t_list		*tokens;

	tokens = NULL;
	tokens = tokenize_input(user_input);
	if (tokens != NULL)
	{
		print_tokens(tokens);
		expand(&tokens, env);
		// remove_quotes();
		command_list = parse_tokens(&tokens);
		if (command_list != NULL)
		{
			terminate_token_list(&tokens);
			print_command_list(command_list);
			terminate_command_list(&command_list);
		}
		else
			*exit_code = EXIT_FAILURE;
	}
	else
		*exit_code = EXIT_FAILURE;
}

int	minishell(t_htable *env)
{
	char	*user_input;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	while (1)
	{
		user_input = readline("--> ");
		if (!(user_input))
		{
			printf("Exiting shell...\n");
			exit(exit_code);
		}
		else
		{
			parse_and_exec(env, user_input, &exit_code);
			printf("Exit code = %i\n", exit_code);
			add_history(user_input);
			free(user_input);
		}
	}
	terminate_hashtable(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_htable	*env;

	env = init_env(envp);
	//print_hashtable(env);
	argc = 0;
	argv = NULL;
	signal(SIGINT, &catch_sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	minishell(env);
	return (EXIT_SUCCESS);
}
