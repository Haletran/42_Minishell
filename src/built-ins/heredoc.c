/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/15 11:14:58 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_heredoc_file(t_cli **cli)
{
	(*cli)->mnsh->heredoc_fd = open("/tmp/.heredoc",
			O_CREAT | O_RDWR | O_APPEND, 0777);
	if ((*cli)->mnsh->heredoc_fd == -1)
	{
		ft_printf_fd(2, HEREDOC_CREATE, strerror(errno), "/tmp/.heredoc");
		(*cli)->mnsh->exit_code = 1;
		close((*cli)->mnsh->heredoc_fd);
		return (ERROR);
	}
	return (SUCCESS);
}

static void	heredoc_fork(t_cli *cli, t_com *tmp)
{
	pid_t	pid;

	pid = fork();
	fork_error(pid);
	if (pid == 0)
		child_process(cli, tmp);
	cli->mnsh->nb_heredoc--;
	waitpid(pid, &cli->mnsh->exit_code, 0);
}

int	ft_heredoc(t_cli *cli)
{
	t_com	*tmp;

	tmp = cli->com;
	if (check_heredoc_error(cli) == ERROR)
		return (ERROR, cli->mnsh->exit_code = 1);
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (cli->mnsh->nb_heredoc - 1 == 0)
				if (create_heredoc_file(&cli) == ERROR)
					return (ERROR);
			if (g_var == 1)
				return (SUCCESS);
			heredoc_fork(cli, tmp);
		}
		tmp = tmp->next;
	}
	cli->mnsh->exit_code = get_exit_code(cli->mnsh);
	close(cli->mnsh->heredoc_fd);
	return (SUCCESS);
}
