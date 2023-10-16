/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:21:03 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/16 14:27:00 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define INCORRECT_USAGE 2

// errors.c
void	*malloc_error_return_null(char *message);
int		malloc_error_return_failure(char *message);
void	*syntax_error_return_null(char *message);
int		syntax_error_return_failure(char *message);

#endif