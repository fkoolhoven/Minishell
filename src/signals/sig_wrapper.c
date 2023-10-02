/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   sig_wrapper.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/02 13:23:00 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/02 13:50:09 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	wrap_sighandler(int signal, t_sighandle handler)
{
	struct sigaction const sigact = {.sa_handler = handler};

	sigaction(signal, &sigact, NULL);
}
