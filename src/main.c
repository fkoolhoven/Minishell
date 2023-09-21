/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/21 18:09:16 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SIMPLE IMPLEMENTATION OF INTERFACE
   Things to change in future:
   			- better exit function which frees everything
			- make sure it gives correct exit status
			- ...

*/

int	main(void)
{
	char			*user_input;
	t_hash_table	*env;

	env = init_env();
	st_print_hashtable(env);
	terminate_hashtable(env);

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
		tokenize_input(user_input);
		add_history(user_input);
		free(user_input);
	}
	return (0);
}
