/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/01 11:53:32 by fkoolhov         ###   ########.fr       */
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

static int	parse_and_exec(t_htable *env, char *input, int ecode, char *cpath)
{
	t_command	*command_list;
	t_list		*tokens;
	int			check;
	int			exit_status;

	exit_status = ecode;
	if (user_input_is_empty(input))
		return (EXIT_SUCCESS);
	tokens = tokenizer(input, &ecode);
	if (tokens == NULL)
		return (ecode);
	if (expand_variables(&tokens, env) == EXIT_FAILURE)
		return (ecode);
	if (remove_quotes_from_tokens(&tokens, &ecode) == EXIT_FAILURE)
		return (ecode);
	command_list = parse(&tokens, &ecode);
	if (command_list == NULL)
		return (ecode);
	terminate_token_list(&tokens);
	check = manage_heredocs(command_list, env);
	if (check != EXIT_SUCCESS)
		return (terminate_command_list(&command_list), check);
	ecode = execute(command_list, env, exit_status, cpath);
	return (ecode);
}

static void	display_banner(void)
{
	printf(BOLDBLUE"\n ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
		" ┃"BOLDPURPLE"☆☆┓☆┏☆☆┓☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆•☆☆•☆┓☆☆☆┓┓╻☆☆"BOLDBLUE"┃\n"
		" ┃"BOLDPURPLE"☆☆┃┃┃┏┓┃┏┏┓┏┳┓┏┓☆☆╋┏┓☆☆┏┳┓┓┏┓┓┏┣┓┏┓┃┃┃☆☆"BOLDBLUE"┃\n"
		" ┃"BOLDPURPLE"☆☆┗┻┛┗☆┗┗┗┛┛┗┗┗☆☆☆┗┗┛☆☆┛┗┗┗┛┗┗┛┛┗┗☆┗┗•☆☆"BOLDBLUE"┃\n"
		" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n"OFF);
}

static int	minishell(t_htable *env, char *cur_path)
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
		else if (!(user_input_is_empty(user_input)))
		{
			exit_code = parse_and_exec(env, user_input, exit_code, cur_path);
			add_history(user_input);
		}
		free(user_input);
	}
	terminate_hashtable(env);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char		tmp[PATH_MAX];
	char		cur_path[PATH_MAX];
	t_htable	*env;

	env = init_env(envp);
	getcwd(tmp, PATH_MAX);
	ft_strlcpy(cur_path, tmp, PATH_MAX);
	argc = 0;
	argv = NULL;
	wrap_sighandler(SIGINT, &catch_sigint_parent);
	wrap_sighandler(SIGQUIT, SIG_IGN);
	return (minishell(env, cur_path));
}
