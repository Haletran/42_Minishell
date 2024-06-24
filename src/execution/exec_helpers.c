/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:25:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/24 17:40:50 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_std(t_cli *cli)
{
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
}

void	wait_process(void)
{
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	reset_redir_values(t_cli *cli)
{
	if (cli->mnsh->heredoc_pipe == 1)
	{
		close(cli->mnsh->heredoc_backup_fd);
		cli->mnsh->heredoc_pipe = 0;
	}
	cli->mnsh->outfile_check = 0;
	cli->mnsh->infile_check = 0;
}
