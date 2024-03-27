/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:03:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/27 16:54:04 by bapasqui         ###   ########.fr       */
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
	signal(CTRL_C, RESET_SIG);
	signal(CTRL_BACKSLACH, RESET_SIG);
	exit(EXIT_SUCCESS);
}

void sig_ctrl_back(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	rl_replace_line("", 1);
	rl_redisplay();
}

/**
 * @brief Handle CTRL+C and CTRL+\ signal
 *
 * @param check to see if heredoc or not
 */
void	handle_sig(int check)
{
	if (check == 1)
	{
		signal(CTRL_C, heredoc_handler);
		signal(CTRL_BACKSLACH, heredoc_handler);
	}
	else if (check == 0)
	{
		signal(CTRL_C, sig_ctrl_c);
		signal(CTRL_BACKSLACH, RESET_SIG);
	}
}
