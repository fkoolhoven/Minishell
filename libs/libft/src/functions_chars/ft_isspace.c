/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_isspace.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 10:21:36 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/18 10:31:15 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ft_isspace:
   		-INPUT:		an integer representing a ascii value
		-OUTPUT:	1 if the given integer c is a space (which is ' ', form-feed,
					newline, carriage return, horizontal tab or vertical tab)
					otherwise, it returns 0
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\t')
		return (1);
	if (c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}
