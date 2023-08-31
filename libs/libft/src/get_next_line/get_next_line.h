/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 18:39:17 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/07 11:45:50 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

size_t	gnl_strlen_n(char *str);
int		gnl_strchr_i(char *str, int c);
void	gnl_mv_buff(char *buff, int fnd_n, int size);
char	*gnl_update_newline(char *line, char *buff, int fnd_n, int size);
char	*get_next_line(int fd);

#endif
