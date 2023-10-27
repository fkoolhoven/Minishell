/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:09:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/10/27 17:20:34 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BOLDGREEN 	"\e[1;32m"
# define BOLDBLUE 	"\e[1;34m"
# define BOLDPURPLE "\e[1;35m"
# define OFF		"\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./types.h"
# include "./utils.h"
# include "./builtins.h"
# include "./executer.h"
# include "./../libs/libft/include/libft.h"
# include "token.h"
# include "expander.h"
# include "parser.h"
# include "signals.h"
# include "executer.h"
# include "errors.h"
# include "env.h"
# include "test.h"

#endif
