/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/11 16:47:23 by bapasqui         ###   ########.fr       */
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
			if (execve(cli->com->env_path, cli->mnsh->commands_recreated,
					cli->mnsh->env_var) == -1)
			{
				cli->mnsh->exit_code = 127;
				printf("minishell: %s: command not found\n", cli->com->command);
				exit(127);
			}
		}
		cli->mnsh->path_command = free_char(cli->mnsh->path_command);
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

	if (check_if_fork(cli->mnsh->commands_recreated, cli->mnsh, cli) == NOT_FOUND)
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
				else
				{
					dup2(cli->mnsh->prev_fd[1], STDOUT_FILENO);
					close(cli->mnsh->prev_fd[1]);
				}
			}
			if (check_commands(cli->mnsh->commands_recreated, cli) == NOT_FOUND)
			{
				if (execve(cli->com->env_path, cli->mnsh->commands_recreated,
						cli->mnsh->env_var) == -1)
				{
					cli->mnsh->exit_code = 127;
					printf(CRESET"minishell: %s: command not found\n", cli->com->command);
					exit(127);
				}
			}
			cli->mnsh->path_command = free_char(cli->mnsh->path_command);
			exit(0);
		}
		waitpid(pid, &cli->mnsh->exit_code, 0);
	}
	close(cli->mnsh->fd[0]);
	close(cli->mnsh->fd[1]);
	close(cli->mnsh->prev_fd[0]);
	close(cli->mnsh->prev_fd[1]);
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
}

void main_loop(t_cli *cli, int count)
{
	if (count != 0)
		cli->mnsh->prev_fd[0] = cli->mnsh->fd[0];
	if (count != cli->mnsh->pipe_count)
		pipe(cli->mnsh->fd);
	if (!cli->com->next)
		execute_last_command(cli);
	else
		piping(cli, count);
}

int get_nb_pipes(t_cli *cli)
{
	t_com	*tmp;
	int		count;

	tmp = cli->com;
	count = 0;
	while (tmp)
	{
		if (tmp->pipe == 1)
			count++;
		tmp = tmp->next;
	}
	return (count);
}


int	exec_pipe(t_cli *cli)
{
	int		count;
	t_cli *tmp;

	count = 0;
	tmp = cli;
	tmp->mnsh->backup[0] = dup(STDIN_FILENO);
	tmp->mnsh->backup[1] = dup(STDOUT_FILENO);
	tmp->mnsh->commands_recreated = NULL;
	cli->mnsh->pipe_count = get_nb_pipes(cli);
	handle_sig(2);
	while (count != cli->mnsh->pipe_count + 1)
	{
		tmp->mnsh->commands_recreated = recreate_commands(cli,tmp->mnsh->commands_recreated);
		if (!tmp->mnsh->commands_recreated)
			return (ERROR);
		if (!cli->com->env_path && cli->token->type != BUILTIN)
		{
			tmp->com->env_path = check_path(tmp->com->command, cli->mnsh);
			if (!tmp->com->env_path)
			{
				cli->mnsh->exit_code = 127;
				break;
			}
		}
		main_loop(tmp, count);
		free_tab(tmp->mnsh->commands_recreated);
		tmp->com = tmp->com->next;
		count++;
	}
	while (waitpid(-1, &cli->mnsh->exit_code, 0) > 0)
		;
	return (SUCCESS);
}
