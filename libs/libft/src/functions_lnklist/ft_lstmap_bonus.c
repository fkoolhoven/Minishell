/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 11:21:23 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:08:25 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions:
			- extra_lstclear()
			- nextra_lstclear()
			- ft_lstmap()
 * extra_lstclear(t_list **lst, void (*del)(void *)):
		This function calls ft_lstclear() and returns NULL.
 * nextra_lstclear(t_list **lst, void (*del)(void *), void *cntt):
		This function deletes the content pointed to by cntt, 
		using the given delete function.
		To clear the list, ft_lstclear() is called.
		The function returns NULL.
 * ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)):
		This function iterates the list lst and 
		applies the given function f on the content of 
		each node to create a new list with.
		If the new content is NULL, nothing can be appended thus
		the function stops iterating and returns NULL.
		If the new node created by calling ft_lstnew() is NULL,
		there is nothing to append to the list and the function 
		stops iterating and returns NULL.
		Otherwise, the function returns the new list.
		ft_lstnew() uses malloc to allocate memory for the new node,
		if one of these fails the rest of the nodes have to be freed.
 */

static t_list	*extra_lstclear(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (0);
}

static t_list	*nextra_lstclear(t_list **lst, void (*del)(void *), void *cntt)
{
	del(cntt);
	ft_lstclear(lst, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head_new;
	t_list	*node;
	t_list	*temp;
	void	*cntt;

	if (lst == NULL)
		return (0);
	temp = lst;
	head_new = NULL;
	while (temp != NULL)
	{
		cntt = f(temp->content);
		if (cntt == NULL)
			return (extra_lstclear(&head_new, del));
		node = ft_lstnew(cntt);
		if (node == NULL)
			return (nextra_lstclear(&head_new, del, cntt));
		ft_lstadd_back(&head_new, node);
		temp = temp->next;
	}
	return (head_new);
}
