/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:03:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 17:42:33 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_ctrl_c(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line(); // double prompt if fork is running
	rl_replace_line("", 1);
	rl_redisplay();
}

void	heredoc_handler(int signum)
{
	(void)signum;
	exit(1);
}

/**
 * @brief Handle CTRL+C and CTRL+\ signal
 *
 * @param signalNum
 */
void	handle_sig(int check)
{
	if (check == 1)
		signal(CTRL_C, heredoc_handler);
	else
		signal(CTRL_C, sig_ctrl_c);
	signal(CTRL_BACKSLACH, RESET_SIG);
}
