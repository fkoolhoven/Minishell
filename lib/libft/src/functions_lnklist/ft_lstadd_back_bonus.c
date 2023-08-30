/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 08:53:07 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:07:21 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_lstadd_back().
 * ft_lstadd_back(t_list **lst, t_list *new):
		If *lst is NULL, the list element new is the first element of the list.
		Otherwise, the function looks for the last element in *lst and sets
		the pointer next in the last list element to the pointer to new.
		This function does not have a return value.
 */

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
