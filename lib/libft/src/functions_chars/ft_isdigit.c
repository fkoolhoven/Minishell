/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:11:27 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 11:33:42 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_isdigit(int nb).
 *ft_isdigit(int nb):
 		This function checks whether the input is represents a digit in ASCII. 
		If the input represents a digit in ASCII the function returns one.
		Otherwise the function returns zero.
 */

int	ft_isdigit(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}
