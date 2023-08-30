/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 18:18:26 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:08:12 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_lstlast(t_list *lst).
 * ft_lstlast(t_list *lst):
		This function traverses the list lst, 
		and returns the pointer to the last element of the list lst.
		If lst is NULL, the function returns NULL.
 */

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr_cur;
	t_list	*ptr_prv;

	if (lst == NULL)
		return (lst);
	ptr_cur = lst;
	ptr_prv = NULL;
	while (ptr_cur != NULL)
	{
		ptr_prv = ptr_cur;
		ptr_cur = ptr_cur->next;
	}
	return (ptr_prv);
}
