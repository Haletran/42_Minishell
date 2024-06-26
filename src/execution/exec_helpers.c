/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:25:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/26 11:50:13 by bapasqui         ###   ########.fr       */
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

int check_er(t_cli *cli)
{
	if (!cli->com->command)
		return (SUCCESS);
	if (ft_isthis(cli->com->command[0], '.') != 0 && ft_strlen(cli->com->command[0]) == 1)
	{
		ft_printf_fd(2, "minishell: %s: filename argument required\n", cli->com->command[0]);
		ft_printf_fd(2, "%s: usage: %s filename [arguments]\n", cli->com->command[0], cli->com->command[0]);
		cli->mnsh->exit_code = 2;
		return (ERROR);
	}
	else if (!ft_strncmp(cli->com->command[0], "..", 2) && ft_strlen(cli->com->command[0]) == 2)
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", cli->com->command[0]);
		cli->mnsh->exit_code = 127;
		return (ERROR);
	}
	else if (!ft_strncmp(cli->com->command[0], "../", 3) && ft_strlen(cli->com->command[0]) == 3)
	{
		ft_printf_fd(2, "minishell: %s: Is a directory\n", cli->com->command[0]);
		cli->mnsh->exit_code = 126;
		return (ERROR);
	}
	return (SUCCESS);
}
