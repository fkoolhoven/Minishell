/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:06:56 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/23 16:58:57 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_free(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (NULL);
}

static int	ft_calc_strl(char *str, int *loc)
{
	int	strlen;

	strlen = 0;
	while (ft_isspace(str[*loc]))
	{
		printf("loop in calc strl1\n");
		(*loc)++;
	}
	if (char_is_quote(str[*loc]))
	{
		strlen = *loc;
		*loc = find_next_quote(str, *loc);
		return (*loc - strlen);
	}
	else
	{
		while (str[*loc] && !ft_isspace(str[*loc]) && !char_is_quote(str[*loc]))
		{
			printf("loop in calc strl2\n");
			(*loc)++;
			strlen++;
		}
	}
	return (strlen);
}

static int	ft_calc_nbr_of_strings(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] != '\0')
	{
		printf("str[i] != '\\0'\n");
		while (ft_isspace(str[i]))
		{
			printf("ft_isspace(str[i])\n");
			i++;
		}
		if (!str[i])
			break ;
		if (char_is_quote(str[i]))
		{
			nbr++;
			i = find_next_quote(str, i);
			if (!str[i])
			{
				printf("SYNTAX ERROR\n");
				return (-1);
			}
		}
		else if (!ft_isspace(str[i]))
		{
			nbr++;
			while (str[i] && !ft_isspace(str[i]) && !char_is_quote(str[i]))
				i++;
		}
	}
	return (nbr);
}

static char	**split_token_value(char *str)
{
	char	**grid;
	int		nbr_of_strings;
	int		loc = 0;
	int		strl;
	int		y;

	nbr_of_strings = ft_calc_nbr_of_strings(str);
	grid = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (grid == NULL)
		return (NULL);
	y = 0;
	strl = 0;
	while (y < nbr_of_strings)
	{
		printf("y < nbr_of_strings, nbr of strings = %i\n", nbr_of_strings);
		strl = ft_calc_strl(str, &loc);
		grid[y] = (char *)malloc(sizeof(char) * strl + 1);
		if (grid[y] == NULL)
			return (ft_free(grid));
		ft_strlcpy(grid[y], &str[loc - strl], strl + 1);
		y++;
	}
	grid[y] = NULL;
	return (grid);
}

int	split_tokens(t_list **list_start, int *exit_code)
{
	t_token	*current_token;
	t_list	*tokens;
	char	**split_value;

	exit_code = 0;
	tokens = *list_start;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		split_value = split_token_value(current_token->value);
		ft_putstr_array_fd(split_value, STDOUT_FILENO);
		// create new tokens and insert
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
