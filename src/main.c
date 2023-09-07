/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/07 18:13:33 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "../libs/libft/include/libft.h"

/* SIMPLE IMPLEMENTATION OF INTERFACE
   Things to change in future:
   			- better exit function which frees everything
			- make sure it gives correct exit status
			- ...

*/

// ctrl-C displays a new prompt on a new line.
// ctrl-D exits the shell.
// ctrl-\ does nothing.


int	main(void)
{

	char	*user_input;

	
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
			tokenize_input(user_input);
			add_history(user_input);
			free(user_input);
		}
	}
	return (0);
}
