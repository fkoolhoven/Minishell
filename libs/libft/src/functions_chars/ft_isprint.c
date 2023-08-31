/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 12:01:02 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 11:36:45 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_isprint(int nb).
 *ft_isprint(int nb):
 		This function returns a one when 
		the input represents a printable character in ASCII.
 		Otherwise, the function returns a zero.
 */

int	ft_isprint(int nb)
{
	if (nb >= 32 && nb <= 126)
		return (1);
	return (0);
}
