/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_free_str_array.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 10:17:55 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/18 10:37:13 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

/* ft_free_str_array:
   		-INPUT:		char **array, a string array which has as last element 
					NULL (NULL terminated string array)
		-OUTPUT:	nothing
		-WORKINGS:	iterates through the array freeing each element,
					then it frees the array
					if the input is NULL, nothing happens
*/

void	ft_free_str_array(char **array)
{
	int	i;

	if (array != NULL)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}
