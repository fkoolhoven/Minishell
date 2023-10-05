/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   sig_wrapper.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/04 12:31:57 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/10/04 12:32:01 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrap_sighandler(int signal, t_sighandle handler)
{
	struct sigaction const sigact = {.sa_handler = handler};

	sigaction(signal, &sigact, NULL);
}
