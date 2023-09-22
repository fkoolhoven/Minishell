/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 16:54:34 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/22 14:51:10 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_htable	*env;
	char		*key;
	char		*value;
	char		*found;
	char		**new_env;
	t_hnode		*node;
//	int			check;

	if (argc < 1 || argv == NULL)
		return (EXIT_FAILURE);
	printf("HELLO I'm in main\n");
	print_strarray(envp);
	env = init_env(envp);
	delete_pair(env, "LS_COLOR");
	delete_pair(env, "DEFAULTS_PATH");
	key = ft_strdup("CATS");
	value = ft_strdup("Lee:Andora:Gato:Sniffels:John:Guusje:");
	add_pair(env, key, value);
	print_hashtable(env);
	node = find_env_valuenode(env, "LESS");
	print_hashnode(node, env);
	node = find_env_valuenode(env, "DEFAULTS_PATH");
	print_hashnode(node, env);
	node = find_env_valuenode(env, "LS_COLORS");
	print_hashnode(node, env);
	node = find_env_valuenode(env, "NONESENSE");
	print_hashnode(node, env);
	found = find_env_value(env, "$CATS");
	printf("Found value: %s\n", found);
	found = find_env_value(env, "NONESENSE");
	printf("Found value: %s\n", found);
	found = find_env_value(env, NULL);
	printf("Found value: %s\n", found);
	found = find_env_value(env, "$PATH");
	printf("Found value: %s\n", found); 
	new_env = convert_htable_to_strarray(env);
//	print_strarray(new_env);
/*	check = comparing_envs(envp, new_env);
	if (check == 0)
		printf("The environments are the same\n");
	else if (check == 1)
		printf("The new environment is missing an element\n");
	else 
		printf("One of the environments is NULL\n"); */
	ft_free_str_array(new_env);
	terminate_hashtable(env);
	return (0);
}
