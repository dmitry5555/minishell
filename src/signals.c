/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:55:59 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 17:56:17 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		printf("ign sign = ctrl_c\n");
		g_status = SIGINT;
	}
	if (sig == SIGQUIT)
	{
		printf("quit sign = ctrl+|\n");
	}
}

// // main for testing signals
// int	main(int argc, char **argv)
// {
// 	while (argv && argc)
// 	{
// 		// signal(SIGINT, sig_hand);
// 		if (g_status == SIGINT)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 		}
// 		else
// 		{
// 			signal(SIGINT, sig_hand);
// 			signal(SIGQUIT, sig_hand);
// 		}
// 	}
// 	return 0;
// }