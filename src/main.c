/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/09 11:41:00 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_and_exec(t_htable *env, char *user_input, int exit_code)
{
	t_command	*command_list;
	t_list		*tokens;
	int			check;

	exit_code = EXIT_FAILURE;
	tokens = NULL;
	tokens = tokenize_input(user_input);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	print_tokens(tokens);
	expand(&tokens, env);
	if (remove_quotes(&tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	command_list = parse_tokens(&tokens);
	terminate_token_list(&tokens);
	if (command_list == NULL)
		return (EXIT_FAILURE);
	print_command_list(command_list);
	check = manage_heredocs(command_list, env);
	if (check != EXIT_SUCCESS)
		return (terminate_command_list(&command_list), check);
	display_heredocs(command_list);
	heredoc_unlinker(command_list);
	terminate_command_list(&command_list);
	return (EXIT_SUCCESS);
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
			exit_code = parse_and_exec(env, user_input, exit_code);
			printf("Exit code = %i\n", exit_code);
			add_history(user_input);
			free(user_input);
		}
	}
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
