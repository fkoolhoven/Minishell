/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 16:54:34 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/20 16:48:03 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_htable	*env;

	if (argc < 1 || argv == NULL)
		return (EXIT_FAILURE);
	printf("HELLO I'm in main\n");
	print_strarray(envp);
	env = init_env(envp);
	print_hashtable(env);
	terminate_hashtable(env);
	return (0);
}
