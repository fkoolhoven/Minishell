/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 18:38:46 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/07 11:47:41 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*get_newline(int fd, int size, int nb_read, char *buff)
{
	char	*line;
	int		fnd_n;

	line = NULL;
	fnd_n = gnl_strchr_i(buff, '\n');
	while (fnd_n < 0 && nb_read > 0)
	{
		line = gnl_update_newline(line, buff, fnd_n, size);
		if (line == NULL)
			return (NULL);
		nb_read = read(fd, buff, size);
		fnd_n = gnl_strchr_i(buff, '\n');
	}
	if (nb_read > 0)
		line = gnl_update_newline(line, buff, fnd_n, size);
	if (line == NULL)
		return (gnl_mv_buff(buff, (int)(gnl_strlen_n(buff) - 1), size + 1), NULL);
	if (nb_read <= 0)
		gnl_mv_buff(buff, (int)(gnl_strlen_n(buff) - 1), size + 1);
	if (nb_read == -1)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	int			nb_read;

	nb_read = 1;
	if (fd < 0)
		return (NULL);
	if (buff[0] == '\0')
		nb_read = read(fd, buff, BUFFER_SIZE);
	if (nb_read <= 0)
		return (NULL);
	return (get_newline(fd, BUFFER_SIZE, nb_read, buff));
}
