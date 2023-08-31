/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:47:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/11 10:34:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the function ft_isalpha(int nb).
 *ft_isalpha(int nb):
 		This function returns one if the input is a ASCII value
	   	representing a lowercase or uppercase letter. 
		Otherwise, it returns a zero.
 */

int	ft_isalpha(int nb)
{
	if ((nb >= 'a' && nb <= 'z') || (nb >= 'A' && nb <= 'Z'))
		return (1);
	return (0);
}
