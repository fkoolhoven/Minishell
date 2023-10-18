/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:38:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/18 12:41:18 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser_test.c TEST FUNCTIONS!
void	print_redirections(t_redirect *lst);
void	print_string_array(char **str_array);
void	print_command_list(t_command *list);

// token_test.c TEST FUNCTIONS!
void	print_tokens(t_list *tokens);

// test_heredoc.c
void	display_file(char *filename);
void	display_heredocs(t_command *cmnd_list);
void	test_heredoc(t_command *cmnd_list, t_htable *env);

// env_functions/test_ft.c 
void	print_hasharray(t_htable *env_table, t_hnode **head);
void	print_strarray(char **envp);
void	print_hashtable(t_htable *env_table);
void	print_hashnode(t_hnode *node, t_htable *env);
int		comparing_envs(char **env, char **new_env);