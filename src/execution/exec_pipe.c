/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/09 19:36:12 by bapasqui         ###   ########.fr       */
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
		if (count != cli->mnsh->pipe_count - 1)
		{
			dup2(cli->mnsh->fd[1], STDOUT_FILENO);
			close(cli->mnsh->fd[1]);
		}
		close(cli->mnsh->fd[0]);
		if (check_commands(cli->mnsh->commands_recreated, cli) == NOT_FOUND)
		{
			if (execve(cli->mnsh->path_command, cli->mnsh->commands_recreated,
					cli->mnsh->env_var) == -1)
			{
				cli->mnsh->exit_code = 127;
				printf("minishell: %s: command not found\n", cli->com->command);
				exit(127);
			}
		}
		free_char(cli->mnsh->path_command);
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

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (cli->mnsh->prev_fd[0] != 0)
		{
			dup2(cli->mnsh->prev_fd[0], STDIN_FILENO);
			close(cli->mnsh->prev_fd[0]);
		}
		else
		{
			dup2(cli->mnsh->prev_fd[1], STDOUT_FILENO);
			close(cli->mnsh->prev_fd[1]);
		}
		if (check_commands(cli->mnsh->commands_recreated, cli) == NOT_FOUND)
		{
			if (execve(cli->mnsh->path_command, cli->mnsh->commands_recreated,
					cli->mnsh->env_var) == -1)
			{
				cli->mnsh->exit_code = 127;
				printf("minishell: %s: command not found\n", cli->com->command);
				exit(127);
			}
		}
		free_char(cli->mnsh->path_command);
		exit(0);
	}
	waitpid(pid, &cli->mnsh->exit_code, 0);
	get_exit_code(cli->mnsh);
	close(cli->mnsh->fd[0]);
	close(cli->mnsh->fd[1]);
	close(cli->mnsh->prev_fd[0]);
	close(cli->mnsh->prev_fd[1]);
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
}

int	loop(t_cli *cli, int count)
{
	if (count != 0)
		cli->mnsh->prev_fd[0] = cli->mnsh->fd[0];
	if (count != cli->mnsh->pipe_count + 1)
		pipe(cli->mnsh->fd);
	if (!cli->com->next == NULL)
		execute_last_command(cli);
	else
		piping(cli, count);
}

int	exec(t_cli *cli)
{
	t_cli	*tmp;
	int		count;

	tmp = cli;
	count = 0;
	cli->mnsh->backup[0] = dup(STDIN_FILENO);
	cli->mnsh->backup[1] = dup(STDOUT_FILENO);
	cli->mnsh->commands_recreated = NULL;
	cli->mnsh->commands_recreated = recreate_commands(cli,
			cli->mnsh->commands_recreated);
	if (!cli->mnsh->commands_recreated)
		return (ERROR);
	handle_sig(2);
	while (tmp->com)
	{
		cli->mnsh->commands_recreated = recreate_commands(cli,
				cli->mnsh->commands_recreated);
		main_loop(cli, count);
		free_tab(cli->mnsh->commands_recreated);
		tmp->com = tmp->com->next;
		count++;
	}
	while (waitpid(-1, cli->mnsh->exit_code, NULL))
		;
	return (SUCCESS);
}
