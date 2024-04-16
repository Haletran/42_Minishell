/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/16 11:25:27 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	piping(char **str, t_lst *args, int i)
{
	pid_t	pid;

	(void)i;
	if (check_if_fork(str, args) == NOT_FOUND)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_printf_fd(2, "fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			if (i != 0)
			{
				dup2(args->prev_fd[0], STDIN_FILENO);
				close(args->prev_fd[0]);
			}
			if (i != args->pipe_count - 1)
			{
				dup2(args->fd[1], STDOUT_FILENO);
				close(args->fd[1]);
			}
			close(args->fd[0]);
			if (check_commands(str, args) == SUCCESS)
				exit(0);
			else if (execve(args->path_command, str, args->env_var) == -1)
				exit(1);
			free_tab(str);
			free_char(args->path_command);
			waitpid(pid, &args->exit_code, 0);
			exit(0);
		}
		else
		{
			if (i != args->pipe_count - 1)
				close(args->fd[1]);
		}
		if (args->path_command != NULL)
			free_char(args->path_command);
		waitpid(pid, &args->exit_code, 0);
	}
}

void execute_last_command(char **str, t_lst *args, int i)
{
	pid_t pid;
	(void)i;
	if (check_if_fork(str, args) == NOT_FOUND)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_printf_fd(2, "fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			if (args->prev_fd[0] != 0)
			{
				dup2(args->prev_fd[0], STDIN_FILENO);
				close(args->prev_fd[0]);
			}
			else
			{
				dup2(args->prev_fd[1], STDOUT_FILENO);
				close(args->prev_fd[1]);
			}
			if (args->outfile)
				dup2(args->file_fd[1], STDOUT_FILENO);
			if (check_commands(str, args) == SUCCESS)
				exit(0);
			else if (execve(args->path_command, str, args->env_var) == -1)
				exit(1);
			free_tab(str);
			free_char(args->path_command);
			exit(0);
		}
		waitpid(pid, &args->exit_code, 0);
	}		
	if (args->path_command != NULL)
			free_char(args->path_command);
	close(args->fd[0]);
	close(args->fd[1]);
	dup2(args->backup[0], STDIN_FILENO);
	close(args->backup[0]);
	dup2(args->backup[1], STDOUT_FILENO);
	close(args->backup[1]);
}

int	check_infile_outfile(t_lst *args)
{
	args->backup[0] = dup(STDIN_FILENO);
	args->backup[1] = dup(STDOUT_FILENO);
	if (args->infile)
	{
		args->file_fd[0] = open(args->infile, O_RDONLY);
		if (args->file_fd[0] == -1)
		{
			ft_printf_fd(2, "minishell: %s: No such file or directory\n",
				args->infile);
			return (ERROR);
		}
		dup2(args->file_fd[0], STDIN_FILENO);
	}
	if (args->outfile)
	{
		args->file_fd[1] = open(args->outfile, O_RDWR | O_CREAT | O_TRUNC, 0640);
		if (args->file_fd[1] == -1)
		{
			ft_printf_fd(2, "minishell: %s: No such file or directory\n",
				args->outfile);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	exec_pipe(char **str, t_lst *args)
{
	int		i;
	char	**tmp;

	i = 0;
	// add infile and outfile support
	if (check_infile_outfile(args) == ERROR)
		return (ERROR);
	args->pipe_count = count_pipe(str);
	handle_sig(2);
	while (str[i])
	{
		tmp = ft_split(str[i], ' ');
		if (check_if_path_needed(tmp) == NOT_FOUND)
			args->path_command = check_path(tmp, args, 0);
		if (i != 0)
			args->prev_fd[0] = args->fd[0];
		if (i != args->pipe_count - 1)
			pipe(args->fd);
		if (!str[i + 1])
			execute_last_command(tmp, args, i);
		else
			piping(tmp, args, i);
		if (tmp != NULL)
			free_tab(tmp);
		i++;
	}
	waitpid(-1, &args->exit_code, 0);
	return (SUCCESS);
}
