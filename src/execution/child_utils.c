/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:25:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/27 23:00:54 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirection_pipe(t_cli *cli)
{
	if (cli->mnsh->outfile_check != 1)
	{
		close(cli->mnsh->fd[0]);
		dup2(cli->mnsh->fd[1], STDOUT_FILENO);
		close(cli->mnsh->fd[1]);
	}
}

void	redirection_fd(t_cli *cli)
{
	close(cli->mnsh->backup[0]);
	close(cli->mnsh->backup[1]);
	if (cli->mnsh->heredoc_pipe == 1)
	{
		dup2(cli->mnsh->heredoc_backup_fd, STDIN_FILENO);
		close(cli->mnsh->heredoc_backup_fd);
	}
}

void	redirection_parent(t_cli *cli)
{
	close(cli->mnsh->fd[1]);
	dup2(cli->mnsh->fd[0], STDIN_FILENO);
	close(cli->mnsh->fd[0]);
}

void	redirection_error(t_cli *cli)
{
	close(cli->mnsh->backup[0]);
	close(cli->mnsh->backup[1]);
	close(cli->mnsh->fd[0]);
	close(cli->mnsh->fd[1]);
	freeway(cli);
	exit(1);
}

int	check_before_exec(t_cli **cli)
{
	if (parsing_check(*cli) == ERROR)
		return (ERROR);
	if (check_error(cli) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
