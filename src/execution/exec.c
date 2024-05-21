/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/21 11:35:17 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	main_loop(t_cli *cli, int count)
{
	if (cli->com->type == COMMAND)
	{
		if (count != 0)
			cli->mnsh->prev_fd[0] = cli->mnsh->fd[0];
		if (!cli->com->next)
			execute_last_command(cli);
		else
		{
			pipe(cli->mnsh->fd);
			piping(cli, count);
		}
		cli->mnsh->heredoc_pipe = 0;
	}
}

int	get_nb_pipes(t_com *com)
{
	int	count;

	count = 0;
	while (com)
	{
		if (com->command)
			count++;
		com = com->next;
	}
	return (count);
}

// LEAKS (fds)
static void	handle_heredoc(t_cli *cli, int *heredoc)
{
	if (ft_heredoc(cli) == ERROR)
		exit(ERROR);
	else if (cli && cli->com && cli->com->command != NULL)
	{
		cli->mnsh->heredoc_backup_fd = open("/tmp/.heredoc", O_RDONLY);
		cli->mnsh->heredoc_pipe = 1;
		*heredoc = 1;
	}
	else
	{
		delete_file("/tmp/.heredoc", cli);
		exit(SUCCESS);
	}
}

static void	loop_commands(t_cli *cli, int *count)
{
	while (cli->com)
	{
		if (parsing_check(cli) == ERROR)
		{
			close(cli->mnsh->backup[0]);
			close(cli->mnsh->backup[1]);
			break ;
		}
		main_loop(cli, *count);
		if (cli->com->next)
			cli->com = cli->com->next;
		else
			break ;
		(*count)++;
	}
}

int	exec_pipe(t_cli *cli)
{
	int	count;
	int	heredoc;

	count = 0;
	handle_sig(2);
	heredoc = 0;
	cli->mnsh->pipe_count = get_nb_pipes(cli->com);
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	cli->mnsh->backup[0] = dup(STDIN_FILENO);
	cli->mnsh->backup[1] = dup(STDOUT_FILENO);
	if (cli->mnsh->nb_heredoc > 0)
		handle_heredoc(cli, &heredoc);
	loop_commands(cli, &count);
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (heredoc == 1)
		delete_file("/tmp/.heredoc", cli);
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
	close_fds();
	return (SUCCESS);
}
