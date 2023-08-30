/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 10:22:58 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/18 09:22:00 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_tolower().
 * ft_tolower(int c)
 		This function returns the lowercase letter in ASCII of c, 
		if c is an uppercase letter in ASCII.
		Otherwise, the function returns c.
		This function is not protected against overflow.
 */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
