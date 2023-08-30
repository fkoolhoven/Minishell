/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 15:36:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:03:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_strdup().
 * ft_strdup(const char *str):
 		This function makes room for a new string using malloc.
		If malloc fails the function returns a NULL-pointer.
		If str is a NULL-pointer, the function returns a NULL-pointer.
		Otherwise, the function calls ft_strlcpy() to 
		copy str in to the new pointer and returns the new pointer.
 */

char	*ft_strdup(const char *str)
{
	char	*ptr_strdup;
	int		len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	ptr_strdup = (char *)malloc(len + 1);
	if (ptr_strdup != NULL)
	{
		ft_strlcpy(ptr_strdup, str, len + 1);
		return (ptr_strdup);
	}
	return (NULL);
}
