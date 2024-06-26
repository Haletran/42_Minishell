/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/26 16:07:38 by bapasqui         ###   ########.fr       */
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

int	ft_heredoc(t_cli *cli)
{
	pid_t	pid;
	t_com	*tmp;

	tmp = cli->com;
	handle_sig(1);
	if (check_heredoc_error(cli) == ERROR)
		return (ERROR, cli->mnsh->exit_code = 1);
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (cli->mnsh->nb_heredoc - 1 == 0)
				if (create_heredoc_file(&cli) == ERROR)
					return (ERROR);
			pid = fork();
			fork_error(pid);
			if (pid == 0)
				child_process(cli, tmp);
			cli->mnsh->nb_heredoc--;
			waitpid(pid, &cli->mnsh->exit_code, 0);
		}
		tmp = tmp->next;
	}
	cli->mnsh->exit_code = get_exit_code(cli->mnsh);
	return (SUCCESS, close(cli->mnsh->heredoc_fd));
}
