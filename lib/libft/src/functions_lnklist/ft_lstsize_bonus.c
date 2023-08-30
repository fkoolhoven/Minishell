/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 16:15:05 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:08:47 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_lstsize().
 * ft_lstsize(t_list *lst):
		This function counts the amount of list elements in the given list lst.
		This even works if lst is NULL.
 */

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		size;

	ptr = lst;
	size = 0;
	while (ptr != NULL)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}
