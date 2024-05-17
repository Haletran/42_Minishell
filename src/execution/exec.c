/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/17 13:10:23 by bapasqui         ###   ########.fr       */
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
						ft_printf_fd(2, CRESET "minishell: %s: command not found\n", *cli->com->command); 
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
	close(cli->mnsh->fd[0]);
	close(cli->mnsh->fd[1]);
	close(cli->mnsh->prev_fd[0]);
	close(cli->mnsh->prev_fd[1]);
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
}

void	main_loop(t_cli *cli, int count)
{
	if (cli->com->type == COMMAND)
	{
		if (count != 0)
			cli->mnsh->prev_fd[0] = cli->mnsh->fd[0];
		if (count != cli->mnsh->pipe_count || cli->mnsh->nb_commands != 1)
			pipe(cli->mnsh->fd);
		if (!cli->com->next)
			execute_last_command(cli);
		else
			piping(cli, count);
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

int	exec_pipe(t_cli *cli)
{
	int		count;
	int		heredoc;

	count = 0;
	cli->mnsh->backup[0] = dup(STDIN_FILENO);
	cli->mnsh->backup[1] = dup(STDOUT_FILENO);
	handle_sig(2);
	heredoc = 0;
	cli->mnsh->nb_commands = get_nb_commands(cli->com);
	cli->mnsh->pipe_count = get_nb_pipes(cli->com);
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	if (cli->mnsh->nb_heredoc > 0)
	{
		if (ft_heredoc(cli) == ERROR)
			return (ERROR);
		else if (cli && cli->com && cli->com->command != NULL)
		{
			cli->mnsh->heredoc_backup_fd = open("/tmp/.heredoc", O_RDONLY);
			cli->mnsh->heredoc_pipe = 1;
			heredoc = 1;
		}
		else
		{
			delete_file("/tmp/.heredoc", cli);
			return (SUCCESS);
		}
	}
	 //check_redirection(cli);
	while (count != cli->mnsh->pipe_count)
	{
		if (parsing_check(cli) == ERROR)
			break ;
		main_loop(cli, count);
		if (cli->com->next)
			cli->com = cli->com->next;
		else
			break ;
		count++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (heredoc == 1)
		delete_file("/tmp/.heredoc", cli);
	close_fds();
	return (SUCCESS);
}
