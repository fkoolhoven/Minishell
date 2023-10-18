/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:17:56 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/18 13:52:42 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*malloc_error_return_null(char *message)
{
	ft_putstr_fd("minishell: malloc error: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (NULL);
}

int	malloc_error_return_failure(char *message)
{
	ft_putstr_fd("minishell: malloc error: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	*syntax_error_return_null(char *message, int *exit_code)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	*exit_code = INCORRECT_USAGE;
	return (NULL);
}

int	syntax_error_return_failure(char *message, int *exit_code)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	*exit_code = INCORRECT_USAGE;
	return (EXIT_FAILURE);
}
