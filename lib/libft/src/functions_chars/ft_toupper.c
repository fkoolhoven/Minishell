/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 10:10:07 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/13 17:35:39 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_toupper().
 * ft_toupper(int c):
 		This function returns the value of c if c 
		does not represent a lowercase letter in ASCII.
		Otherwise, the function returns the ASCII value of 
		the uppercase letter c represents.
		The function is not protected against overflow.
 */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
