/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:55:59 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 21:22:16 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		//printf("ign sign = ctrl_c\n");
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI , "\n"); //mimics pressing the Enter key
		rl_replace_line("", 0); //clears out;
		rl_on_new_line(); //moves cursor to new line
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