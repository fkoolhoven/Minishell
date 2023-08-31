/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 13:00:43 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:04:12 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the function ft_strmapi().
 * ft_strmapi(char const *s, char (*)(unsigned int, char)):
		This function creates a new string using malloc.
		If malloc fails, the function returns NULL.
		The new string is filled with characters obtained 
		by the calling the given f(i, *(s+i)).
		The new string is null-terminated.
		The function returns the new string.
		If s is NULL, the function returns NULL.
 */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr_mapi;
	size_t			len_s;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	ptr_mapi = (char *)malloc(len_s + 1);
	if (ptr_mapi == NULL)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(ptr_mapi + i) = f(i, *(s + i));
		i++;
	}
	*(ptr_mapi + i) = '\0';
	return (ptr_mapi);
}
