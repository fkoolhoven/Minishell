/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/29 15:55:34 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_cmndlist(t_command *cmnd_list)
{
	int	i;
	
	if (cmnd_list == NULL)
		return (0);
	i = 0;
	while (cmnd_list != NULL)
	{
		cmnd_list = cmnd_list->next;
		i++;
	}
	return (i);
}

int	execute_builtin(t_exec_var *var, t_command *cmnd, int bltin)
{
	t_f_bltin 	jmptbl[7];

	jmptbl[0] = NULL;
	jmptbl[1] = NULL;
	jmptbl[2] = NULL;
	jmptbl[3] = NULL;
	jmptbl[4] = &export;
	jmptbl[5] = NULL;
	jmptbl[6] = NULL;

	if (bltin >= 0 && bltin <= 6)
		return (jmptbl[bltin](var, cmnd));
	else
		return (jmptbl[(bltin % 7)](var, cmnd));
}


int	execute(t_command *cmnd_list, t_htable *environ)
{
	t_exec_var	var;
	int			fd[2];

	if (cmnd_list != NULL && environ != NULL)
	{
		var.cmnd_list = cmnd_list;
		var.env = environ;
		var.env_str = convert_htable_to_strarray(environ); 
		if (var.env_str == NULL)
			return (EXIT_FAILURE);
		var.fd_pipe = fd;
		var.process = 1;
		var.last_cmnd = size_cmndlist(cmnd_list);
		execute_builtin(&var, cmnd_list, 4);
	}
	return (EXIT_FAILURE);
}


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
		command_list = parse_tokens(&tokens);
		if (command_list != NULL)
		{
			terminate_token_list(&tokens);
			print_command_list(command_list);
			execute(command_list, env);
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
