/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:47:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/21 10:06:07 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	piping(t_cli *cli, int count)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (count != 0)
		{
			dup2(cli->mnsh->prev_fd[0], STDIN_FILENO);
			close(cli->mnsh->prev_fd[0]);
		}
		if (cli->mnsh->heredoc_pipe == 1)
		{
			dup2(cli->mnsh->heredoc_backup_fd, STDIN_FILENO);
			close(cli->mnsh->heredoc_backup_fd);
		}
		if (count != cli->mnsh->pipe_count - 1)
		{
			dup2(cli->mnsh->fd[1], STDOUT_FILENO);
			close(cli->mnsh->fd[1]);
		}
		close(cli->mnsh->fd[0]);
		if (check_commands(cli->com->command, cli) == NOT_FOUND)
		{
			if (execve(cli->com->env_path, cli->com->command,
					cli->mnsh->env_var) == -1)
			{
				cli->mnsh->exit_code = 127;
				ft_printf_fd(2, "minishell: %s: command not found\n",
					*cli->com->command);
				ft_exitcode(127);
			}
		}
		if (check_if_builtin(cli->com->command[0]) == SUCCESS)
			ft_exitcode(0);
	}
	else
	{
		if (count != cli->mnsh->pipe_count - 1)
			close(cli->mnsh->fd[1]);
	}
}

void	execute_last_command(t_cli *cli)
{
	pid_t	pid;

	if (check_if_fork(cli->com->command, cli->mnsh, cli) == NOT_FOUND)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_printf_fd(2, "fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			if (cli->mnsh->pipe_count != 0)
			{
				if (cli->mnsh->prev_fd[0] != 0)
				{
					dup2(cli->mnsh->prev_fd[0], STDIN_FILENO);
					close(cli->mnsh->prev_fd[0]);
				}
				else if (cli->mnsh->heredoc_pipe == 1)
				{
					dup2(cli->mnsh->heredoc_backup_fd, STDIN_FILENO);
					close(cli->mnsh->heredoc_backup_fd);
				}
			}
			if (check_commands(cli->com->command, cli) == NOT_FOUND)
			{
				if (execve(cli->com->env_path, cli->com->command,
						cli->mnsh->env_var) == -1)
				{
					if (ft_strlen(cli->com->command[0]) != 0)
					{
						cli->mnsh->exit_code = 127;
						ft_printf_fd(2, CRESET "minishell: \
							%s: command not found\n", *cli->com->command);
						ft_exitcode(127);
					}
				}
				exit(0);
			}
		}
		waitpid(pid, &cli->mnsh->exit_code, 0);
	}
	if (cli->mnsh->exit_code != 127 && check_if_forked(cli) == NOT_FOUND)
		cli->mnsh->exit_code = get_exit_code(cli->mnsh);
	close(cli->mnsh->prev_fd[0]);
	close(cli->mnsh->prev_fd[1]);
	close(cli->mnsh->fd[0]);
	close(cli->mnsh->fd[1]);
}
