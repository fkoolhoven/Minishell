/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_array_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:51:12 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/09 16:02:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_array_fd(char **str_array, int fd)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		ft_putendl_fd(str_array[i], fd);
		i++;
	}
}
