/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/06 16:26:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_and_exec(t_htable *env, char *user_input, int exit_code)
{
	t_command	*command_list;
	t_list		*tokens;
	int			check;

	exit_code = 1;
	tokens = NULL;
	tokens = tokenize_input(user_input);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	print_tokens(tokens);
	expand(&tokens, env);
	command_list = parse_tokens(&tokens);
	if (command_list == NULL)
		return (EXIT_FAILURE);
	terminate_token_list(&tokens);
	print_command_list(command_list);
	check = manage_heredocs(command_list, env);
	if (check != EXIT_SUCCESS)
		return (terminate_command_list(&command_list), check);
	display_heredocs(command_list);
	printf("Going to execute !!!!\n");
	exit_code = execute(command_list, env);
	printf("Finished executing\n");
	heredoc_unlinker(command_list);
	terminate_command_list(&command_list);
	return (exit_code);
}

int	minishell(t_htable *env)
{
	char	*user_input;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	while (1)
	{
	//	printf("In beginning while loop\n");
		user_input = readline("--> ");
		if (!(user_input))
		{
			printf("Exiting shell...\n");
			exit(exit_code);
		}
		else
		{
			exit_code = parse_and_exec(env, user_input, exit_code);
			printf("Exit code = %i\n", exit_code);
			add_history(user_input);
		//	printf("\n");
		//	rl_on_new_line();
		//	rl_replace_line("", 0);
		//	rl_redisplay();
		}
	//	printf("In ending while loop\n");
		free(user_input);
	}
	printf("Ended while loop\n");
	terminate_hashtable(env);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_htable	*env;

	env = init_env(envp);
	//print_hashtable(env);
	argc = 0;
	argv = NULL;
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	wrap_sighandler(SIGQUIT, SIG_IGN);
	return (minishell(env));
}
