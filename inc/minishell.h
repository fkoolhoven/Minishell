/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/08/31 14:59:28 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/include/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum e_type
{
	WORD,
	PIPE,
	HEREDOC,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND
};

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}	t_token;

void	tokenize_input(char *input);
