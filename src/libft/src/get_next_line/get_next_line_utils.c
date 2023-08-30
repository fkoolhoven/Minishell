/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 18:44:09 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/07 11:49:00 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	gnl_strlen_n(char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	gnl_strchr_i(char *str, int c)
{
	char	cp_c;
	int		cnt;

	if (str == NULL)
		return (-1);
	cp_c = c;
	cnt = 0;
	while (str[cnt] && str[cnt] != cp_c)
		cnt++;
	if (!(str[cnt]))
		return (-1);
	return (cnt);
}

void	gnl_mv_buff(char *buff, int fnd_n, int size)
{
	int	i;
	int	j;

	i = fnd_n + 1;
	j = 0;
	while (*(buff + i + j))
	{
		*(buff + j) = *(buff + i + j);
		j++;
	}
	while (j < size)
	{
		*(buff + j) = '\0';
		j++;
	}
}

static char	*gnl_mk_line(char *temp, char *buff, int fnd_n)
{
	char	*line;
	int		i;
	int		j;

	if (fnd_n < 0)
		fnd_n = gnl_strlen_n(buff) - 1;
	line = (char *)malloc(gnl_strlen_n(temp) + fnd_n + 2);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (*(temp + i))
	{
		*(line + i) = *(temp + i);
		i++;
	}
	j = 0;
	while (*(buff + j) && j <= fnd_n)
	{
		*(line + i + j) = *(buff + j);
		j++;
	}
	*(line + i + j) = '\0';
	return (line);
}

char	*gnl_update_newline(char *line, char *buff, int fnd_n, int size)
{
	char	*newline;

	if (line == NULL)
		newline = gnl_mk_line("", buff, fnd_n);
	else
		newline = gnl_mk_line(line, buff, fnd_n);
	if (line != NULL)
		free(line);
	if (fnd_n < 0)
		gnl_mv_buff(buff, (int)(gnl_strlen_n(buff) - 1), size + 1);
	else
		gnl_mv_buff(buff, fnd_n, size + 1);
	return (newline);
}
