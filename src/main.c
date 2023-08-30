/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:08:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/30 17:00:23 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	main(void)
{
	int	i;
	char	*user_input;

	i = 1;
	while (i > 0)
	{
		user_input = readline("Give input here --> ");
		if (ft_strnstr(user_input, "exit", ft_strlen(user_input)) != NULL)
		{
			free(user_input);
			printf("Exiting ...\n");
			i = -1;
		}
		printf("Received user_input, commencing process\n");
		free(user_input);
	}
	return (0);
}
