/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:47:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/12 13:44:05 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_error(t_cli **cli)
{
	t_com	*tmp;

	tmp = (*cli)->com;
	if (!tmp)
		return (ERROR);
	while (tmp)
	{	
		if (check_if_path_needed(tmp->command) == NOT_FOUND)
		{
			if (access(tmp->env_path, F_OK) == -1)
			{
				(*cli)->mnsh->exit_code = 127;
				print_error(NOT_FOUND, (*cli)->com->command[0]);
				return (ERROR);
			}
/* 			else if (tmp->command[0][0] == '\0')
			{
				(*cli)->mnsh->exit_code = 127;
				print_error(NOT_FOUND, (*cli)->com->command[0]);
				return (ERROR);
			} */
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void execute_command(t_cli *cli)
{		
	if (check_commands(cli->com->command, cli) == NOT_FOUND)
	{
		if (execve(cli->com->env_path, cli->com->command,
				cli->mnsh->env_var) == -1)
			ft_exitcode(cli, cli->mnsh->exit_code);
	}
	if (check_if_builtin(cli->com->command[0]) == SUCCESS)
		ft_exitcode(cli, cli->mnsh->exit_code);
}

void fork_error()
{
	print_error(FORK_FAILED, NULL);
	exit(1);
}

void	piping(t_cli *cli, int count)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_error();
	else if (pid == 0)
	{
		if (cli->mnsh->heredoc_pipe == 1)
		{
			dup2(cli->mnsh->heredoc_backup_fd, STDIN_FILENO);
			close(cli->mnsh->heredoc_backup_fd);
		}
		if (count != cli->mnsh->pipe_count)
		{
			if (cli->mnsh->outfile_check == 1)
			{
				dup2(cli->mnsh->outfile_fd, STDOUT_FILENO);
				close(cli->mnsh->outfile_fd);
			}
			if (cli->mnsh->infile_check == 1)
			{
				dup2(cli->mnsh->infile_fd, STDIN_FILENO);
				close(cli->mnsh->infile_fd);
			}
			if (cli->mnsh->outfile_check != 1)
			{
				dup2(cli->mnsh->fd[1], STDOUT_FILENO);
				close(cli->mnsh->fd[1]);
			}
		}
		close(cli->mnsh->fd[0]);
		if (check_commands(cli->com->command, cli) == NOT_FOUND)
		{
			if (execve(cli->com->env_path, cli->com->command,
				cli->mnsh->env_var) == -1)
				ft_exitcode(cli, cli->mnsh->exit_code);
		}
		if (check_if_builtin(cli->com->command[0]) == SUCCESS)
			ft_exitcode(cli, cli->mnsh->exit_code);
	}
	else
	{
		if (count != cli->mnsh->pipe_count)
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
			print_error(FORK_FAILED, NULL);
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
			}
			if (cli->mnsh->heredoc_pipe == 1)
			{
				dup2(cli->mnsh->heredoc_backup_fd, STDIN_FILENO);
				close(cli->mnsh->heredoc_backup_fd);
			}
			if (cli->mnsh->outfile_check == 1)
			{
				dup2(cli->mnsh->outfile_fd, STDOUT_FILENO);
				close(cli->mnsh->outfile_fd);
			}
			if (cli->mnsh->infile_check == 1)
			{
				dup2(cli->mnsh->infile_fd, STDIN_FILENO);
				close(cli->mnsh->infile_fd);
			}
			if (check_commands(cli->com->command, cli) == NOT_FOUND)
			{
				if (execve(cli->com->env_path, cli->com->command,
					cli->mnsh->env_var) == -1)
					ft_exitcode(cli, cli->mnsh->exit_code);
			}
			if (check_if_builtin(cli->com->command[0]) == SUCCESS)
				ft_exitcode(cli, cli->mnsh->exit_code);
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
