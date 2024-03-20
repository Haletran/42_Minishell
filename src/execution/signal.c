/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:03:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/20 15:32:02 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_ctrl_c(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_command_is_running(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
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
 * @param check to see if heredoc or not
 */
void	handle_sig(int check)
{
	if (check == 1)
		signal(CTRL_C, heredoc_handler);
	else
		signal(CTRL_C, sig_ctrl_c);
	signal(CTRL_BACKSLACH, RESET_SIG);
}
