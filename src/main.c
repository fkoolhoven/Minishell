/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/16 16:26:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	user_input_is_empty(char *user_input)
{
	int	i;

	i = 0;
	while (ft_isspace(user_input[i]))
		i++;
	if (user_input[i] == '\0')
		return (true);
	else
		return (false);
}

static int	parse_and_exec(t_htable *env, char *user_input, int exit_code)
{
	t_command	*command_list;
	t_list		*tokens;
	int			check;

	if (user_input_is_empty(user_input))
		return (EXIT_SUCCESS);
	tokens = tokenizer(user_input);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (expand_tokens(&tokens, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (remove_quotes_from_tokens(&tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	command_list = parse(&tokens);
	if (command_list == NULL)
		return (EXIT_FAILURE);
	terminate_token_list(&tokens);
	check = manage_heredocs(command_list, env);
	if (check != EXIT_SUCCESS)
		return (terminate_command_list(&command_list), check);
	exit_code = execute(command_list, env, exit_code);
	heredoc_unlinker(command_list);
	terminate_command_list(&command_list);
	return (exit_code);
}

static void	display_banner(void)
{
	printf(BOLDBLUE"\n ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
		" ┃"BOLDPURPLE"☆☆┓☆┏☆☆┓☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆•☆☆•☆┓☆☆☆┓┓╻☆☆"BOLDBLUE"┃\n"
		" ┃"BOLDPURPLE"☆☆┃┃┃┏┓┃┏┏┓┏┳┓┏┓☆☆╋┏┓☆☆┏┳┓┓┏┓┓┏┣┓┏┓┃┃┃☆☆"BOLDBLUE"┃\n"
		" ┃"BOLDPURPLE"☆☆┗┻┛┗☆┗┗┗┛┛┗┗┗☆☆☆┗┗┛☆☆┛┗┗┗┛┗┗┛┛┗┗☆┗┗•☆☆"BOLDBLUE"┃\n"
		" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n"OFF);
}

static int	minishell(t_htable *env)
{
	char	*user_input;
	int		exit_code;

	display_banner();
	exit_code = EXIT_SUCCESS;
	while (1)
	{
		user_input = readline(BOLDBLUE"minishell » "OFF);
		if (!(user_input))
		{
			terminate_hashtable(env);
			printf(BOLDGREEN"Bye bye! See you next time.\n"OFF);
			exit(exit_code);
		}
		else
		{
			exit_code = parse_and_exec(env, user_input, exit_code);
			printf("Exit code = %i\n", exit_code);
			add_history(user_input);
		}
		free(user_input);
	}
	terminate_hashtable(env);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_htable	*env;

	env = init_env(envp);
	argc = 0;
	argv = NULL;
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	wrap_sighandler(SIGQUIT, SIG_IGN);
	return (minishell(env));
}
