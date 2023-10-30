/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                 :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:05:59 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/30 17:12:54 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	st_error(char *message)
{
	ft_putstr_fd("Heredoc: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	return (EXIT_FAILURE);
}

static char	*st_give_filename(char *s_nb1, int j)
{
	char	*tmp;
	char	*filename;
	char	*s_nb2;

	if (s_nb1 == NULL)
		return (NULL);
	s_nb2 = ft_itoa_base(j, 16, "0123456789ABCDEF");
	if (s_nb2 == NULL)
		return (NULL);
	tmp = ft_strjoin(".HEREDOC", s_nb1);
	if (tmp == NULL)
		return (free(s_nb2), NULL);
	filename = ft_strjoin(tmp, s_nb2);
	free(s_nb2);
	free(tmp);
	return (filename);
}

static int	st_manage_heredocs(t_redirect *in, char *s_nb1, t_htable *env)
{
	int			j;
	int			check;
	char		*filename;

	if (in == NULL)
		return (EXIT_FAILURE);
	if (s_nb1 == NULL)
		return (st_error("generating filename failed\n"));
	j = 0;
	check = EXIT_SUCCESS;
	while (in != NULL)
	{
		if (in->type == HEREDOC)
		{
			filename = st_give_filename(s_nb1, j);
			if (filename != NULL)
				check = manage_one_heredoc(filename, in, env);
			else
				check = st_error("generating filename failed\n");
			j++;
		}
		if (check != EXIT_SUCCESS)
			return (check);
		in = in->next;
	}
	return (check);
}

static int	st_check_manage_heredocs(t_redirect *in, int i, t_htable *env)
{
	char	*s_nb1;
	int		check;

	if (in != NULL)
	{
		s_nb1 = ft_itoa_base(i, 16, "0123456789ABCDEF");
		check = st_manage_heredocs(in, s_nb1, env);
		if (s_nb1 != NULL)
			free(s_nb1);
		return (check);
	}
	return (EXIT_SUCCESS);
}

int	manage_heredocs(t_command *command_list, t_htable *env)
{
	t_command	*tmp;
	int			i;
	int			check;

	if (command_list == NULL || env == NULL)
		return (EXIT_FAILURE);
	tmp = command_list;
	i = 0;
	check = EXIT_SUCCESS;
	while (tmp != NULL)
	{
		if (tmp->in != NULL)
		{
			check = st_check_manage_heredocs(tmp->in, i, env);
			i++;
		}
		if (check != EXIT_SUCCESS)
			return (heredoc_unlinker(command_list), check);
		tmp = tmp->next;
	}
	return (check);
}
