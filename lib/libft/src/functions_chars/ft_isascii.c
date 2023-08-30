/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:57:07 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 11:24:28 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_isascii(int nb).
 *ft_isascii(int nb):
 		This function checks whether the input is an ASCII value.
		It returns one if nb is an ASCII value.
		Otherwise, it returns zero.
 */

int	ft_isascii(int nb)
{
	if (nb >= 0 && nb <= 127)
		return (1);
	return (0);
}
