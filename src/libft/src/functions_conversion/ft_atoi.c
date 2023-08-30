/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:22:13 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/01/18 09:49:03 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

/*This file contains the functions:
			- ft_isspace(int)
			- rec_atoi(const char *, int, int)
			- ft_atoi(const char *)
 *ft_isspace(int c):
 		Checks whether c is a space character in ASCII. 
 		If c is a space character, the function returns one.
		Else it returns zero.
 *rec_atoi(const char *str, int nb, int sgn):
 		Recursively converts the string pointed to by str to an int, 
 		which is stored in nb. 
 		This function returns an int.
		A proper string:
			-Space characters are allowed at the beginning of the string
			-One +/- sign is allowed before the numbers in the string
			-The string should only contain the above described rules and digits.
		If a string is given which does not obey the rules for a proper string,
		this function stops when the rules are broken 
		and returns the integer nb found until then.
 *ft_atoi(const char *str):
 		First checks whether str is a NULL-pointer or not. 
 		If str is not a NULL-pointer, 
		then the function rec_atoi() is called.
		This function returns an int.
 */

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	rec_atoi(const char *str, int nb, int sgn)
{
	if (*str == '\0')
		return (nb);
	else if (ft_isspace(*str) == 1)
	{
		if (sgn != 0 || nb != 0)
			return (nb);
		return (rec_atoi(str + 1, nb, sgn));
	}
	else if (*str == '-' || *str == '+')
	{
		if (*str == '-' && sgn == 0)
			return (rec_atoi(str + 1, nb, -1));
		else if (*str == '+' && sgn == 0)
			return (rec_atoi(str + 1, nb, 1));
		else
			return (nb);
	}
	else if (*str >= '0' && *str <= '9')
	{
		if (sgn == 1 || sgn == 0)
			return (rec_atoi(str + 1, nb * 10 + (*str - '0'), 1));
		return (rec_atoi(str + 1, nb * 10 - (*str - '0'), sgn));
	}
	else
		return (nb);
}

int	ft_atoi(const char *str)
{
	int	nb;

	if (str == NULL)
		return (0);
	nb = rec_atoi(str, 0, 0);
	return (nb);
}
