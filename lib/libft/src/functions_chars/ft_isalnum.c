/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:50:33 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 10:31:14 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_isalnum(int nb).
 *ft_isalnum(int nb):
 		This function checks whether the character given as an int in ASCII value,
	   	is a capital letter, lowercase letter or a number in ASCII value.
		If the input is not one of these, the function returns a zero.
		Otherwise, the function returns one.
 */

int	ft_isalnum(int nb)
{
	if ((nb >= 'A' && nb <= 'Z') || (nb >= 'a' && nb <= 'z'))
		return (1);
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}
