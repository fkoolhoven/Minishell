/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 09:27:22 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 17:03:55 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*This file contains the functions:
 				-ft_am_subs()
				-ft_free_extra()
				-fill_ptr_subs()
				-ft_split()
 * ft_am_subs(char const *s, char c):
 		This function determines the amount of substrings 
		in s with the delimiter c.
		It does this by checking if it found a character 
		which is not the delimiter,
		and then checks where the next delimiter is.
		It returns the amount of substrings found.
 * ft_free_extra(char **ptr_subs, int cnt_subs, int am_subs):
 		This function first frees the entries in 
		the the double pointer until cnt_subs, 
		and frees the entry am_subs.
		Then it frees the double pointer.
		This function always returns zero.
 * fill_ptr_subs(char const *s, char c, char **ptr_subs, int am_subs):
		This function fills the double pointer with 
		the substrings in s between the delimiter c.
		For this the function uses malloc.
		If malloc at some point fails, every entry in the double pointer
		and the double pointer is freed by calling ft_free_extra().
		If a malloc fails, the function returns the return value of ft_free_extra().
		Otherwise, the function returns one.
 * ft_split(char const *s, char c)
		This function creates an array of strings, containing substrings of s
		obtained by splitting s using the character c as a delimiter.
		If s is NULL, the function returns NULL.
		If s only contains the null-terminator, 
		the function returns an array with a string containing the null-terminator
		which ends with a NULL entry.
		Otherwise, the amount of substrings is determined by calling ft_am_subs()
		and an array is created using malloc.
		If the malloc fails the function will return NULL.
		Then the array will be filled with the substrings by calling fill_ptr_subs().
		If fill_ptr_subs() returns zero a malloc failed, so the function returns NULL.
		Otherwise, the function returns the array of substrings.
 */

static int	ft_am_subs(char const *s, char c)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			j = 0;
			while (*(s + i + j) != c && *(s + i + j))
				j++;
			cnt++;
			i = i + j;
		}
		else
			i++;
	}
	return (cnt);
}

static int	ft_free_extra(char **ptr_subs, int cnt_subs, int am_subs)
{
	int	k;

	k = 0;
	while (k < cnt_subs)
	{
		free(ptr_subs[k]);
		k++;
	}
	free(ptr_subs[am_subs]);
	free(ptr_subs);
	return (0);
}

static int	fill_ptr_subs(char const *s, char c, char **ptr_subs, int am_subs)
{
	int	i;
	int	j;
	int	cnt_subs;

	i = 0;
	cnt_subs = 0;
	ptr_subs[am_subs] = NULL;
	while (*(s + i) && cnt_subs < am_subs)
	{
		j = 0;
		if (*(s + i) != c)
		{
			while (*(s + i + j) != c && *(s + i + j))
				j++;
			ptr_subs[cnt_subs] = (char *)malloc(j + 1);
			if (ptr_subs[cnt_subs] == NULL)
				return (ft_free_extra(ptr_subs, cnt_subs, am_subs));
			ft_strlcpy(ptr_subs[cnt_subs], (s + i), j + 1);
			cnt_subs++;
			i = i + j;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		am_subs;
	char	**ptr_subs;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		ptr_subs = (char **)malloc(1 * sizeof(char *));
		if (ptr_subs != NULL)
		{
			ptr_subs[0] = NULL;
			return (ptr_subs);
		}
		return (NULL);
	}
	am_subs = ft_am_subs(s, c);
	ptr_subs = (char **)malloc((am_subs + 1) * sizeof(char *));
	if (ptr_subs == NULL)
		return (NULL);
	if (fill_ptr_subs(s, c, ptr_subs, am_subs) == 0)
		return (NULL);
	return (ptr_subs);
}
