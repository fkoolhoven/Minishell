/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 15:45:00 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:07:31 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_lstadd_front().
 * ft_lstadd_front(t_list **lst, t_list *new):
		This function adds the list element new to the front of the list *lst.
		If new or lst is NULL, the function does not do anything.
 */

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL && lst != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
