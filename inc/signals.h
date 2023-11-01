/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:09:22 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/11/01 14:02:37 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "./types.h"

// signals.c
void	catch_sigint_parent(int sig);
void	catch_sigint_heredoc(int sig);

//sig_wrapper.c 
void	wrap_sighandler(int signal, t_sighandle handler);

#endif
