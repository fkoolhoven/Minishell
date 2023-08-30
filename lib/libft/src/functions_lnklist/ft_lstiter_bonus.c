/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 09:12:14 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:08:01 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_lstiter().
 * ft_lstiter(t_list *lst, void (*f)(void *)):
 		This function iterates through the list lst and
		applies the given function f on the content of each 
		list element (node).
		This function has no return value.
 */

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		f(temp->content);
		temp = temp->next;
	}
}
