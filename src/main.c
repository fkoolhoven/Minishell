/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/31 13:16:33 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	main(void)
{
	char	*user_input;
	char	*buff;
	char	*tmp;
	char	newline[2];

	newline[0] = (char)92;
	newline[1] = '\0';
	printf("%s \n", newline);
	while (1)
	{
		user_input = readline("--> ");
		if (!(user_input))
		{
			printf("Exiting... because input empty\n");
			exit(EXIT_SUCCESS);
		}
		if (ft_strnstr(user_input, "exit", ft_strlen(user_input)) != NULL)
		{
			free(user_input);
			printf("Exiting ...\n");
			exit(EXIT_SUCCESS);
		}
		if (ft_strnstr(user_input, newline, ft_strlen(user_input)) != NULL)
		{
			printf("Newline\n");
			buff = ft_strdup(user_input);
			free(user_input);
			rl_on_new_line();
			user_input = readline("-> ");
			printf("Current user_input: %s \n", user_input);
			printf("Current buff: %s\n", buff);
			while (ft_strnstr(user_input, newline, ft_strlen(user_input)) != NULL)
			{
				tmp = buff;
				buff = ft_strjoin(tmp, user_input);
				free(tmp);
				free(user_input);
				rl_on_new_line();
				user_input = readline("-> ");
				if (ft_strnstr(user_input, "exit", ft_strlen(user_input)) != NULL)
				{
					free(user_input);
					free(buff);
					printf("Exiting ...\n");
					exit(EXIT_SUCCESS);
				}
				printf("Current user_input: %s \n", user_input);
				printf("Current buff: %s\n", buff);
			}
			printf("Current buff: %s \n", buff);
			free(buff);
		}
		/* PROBLEM:
					When compiling the compiler sees rl_replace_line as an invalid function,
					so it seems not to be able to find the function in the readline library.
					I've looked up this problem and found one stackexchange discussion.
					They had a rather long solution for this, but I'm not even sure we have
					to use this function.
					So I am gonna leave it for now...
		if (ft_strnstr(user_input, "hello", ft_strlen(user_input)) != NULL)
		{
			rl_replace_line("hello world", 1);
			rl_redisplay();
		} */
		free(user_input);
	}
	return (0);
}
