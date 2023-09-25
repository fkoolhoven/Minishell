/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/09/25 15:42:27 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "./types.h"
# include "./executer.h"
# include <ctype.h> // we should add our own isspace() to libft!
# include "./../libs/libft/include/libft.h"
# include "token.h"
# include "parser.h"
# include "expand.h"
# include "signals.h"
# include "env.h"

#endif
