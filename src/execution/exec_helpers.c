/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:25:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/27 08:57:30 by bapasqui         ###   ########.fr       */
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

int	check_er(t_cli *cli)
{
	char	**tmp;

	tmp = cli->com->command;
	if (!cli->com->command)
		return (SUCCESS);
	if (ft_isthis(tmp[0], '.') != 0 && ft_strlen(tmp[0]) == 1)
	{
		ft_printf_fd(2, CHECK_ER_ARG_REQ, tmp[0]);
		ft_printf_fd(2, CHECK_ER_USAGE, tmp[0], tmp[0]);
		cli->mnsh->exit_code = 2;
		return (ERROR);
	}
	else if (!ft_strncmp(tmp[0], "..", 2) && ft_strlen(tmp[0]) == 2)
	{
		ft_printf_fd(2, CHECK_ER_CMD_NOT_FOUND, tmp[0]);
		cli->mnsh->exit_code = 127;
		return (ERROR);
	}
	else if (!ft_strncmp(tmp[0], "../", 3) && ft_strlen(tmp[0]) == 3)
	{
		ft_printf_fd(2, CHECK_ER_IS_DIR, tmp[0]);
		cli->mnsh->exit_code = 126;
		return (ERROR);
	}
	return (SUCCESS);
}
