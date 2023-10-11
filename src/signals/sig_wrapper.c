/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:31:57 by jhendrik          #+#    #+#             */
/*   Updated: 2023/10/11 17:03:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrap_sighandler(int signal, t_sighandle handler)
{
	struct sigaction const	sigact = {.sa_handler = handler};

	sigaction(signal, &sigact, NULL);
}
