/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 13:58:59 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	piping(char **str, t_lst *mnsh, int i)
{
	pid_t	pid;

	(void)i;
	if (check_if_fork(str, mnsh) == NOT_FOUND)
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
				dup2(mnsh->prev_fd[0], STDIN_FILENO);
				close(mnsh->prev_fd[0]);
			}
			if (i != mnsh->pipe_count - 1)
			{
				dup2(mnsh->fd[1], STDOUT_FILENO);
				close(mnsh->fd[1]);
			}
			close(mnsh->fd[0]);
			if (check_commands(str, mnsh) == SUCCESS)
				exit(0);
			else if (execve(mnsh->path_command, str, mnsh->env_var) == -1)
				exit(1);
			free_tab(str);
			free_char(mnsh->path_command);
			exit(0);
		}
		else
		{
			if (i != mnsh->pipe_count - 1)
				close(mnsh->fd[1]);
		}
		if (mnsh->path_command != NULL)
			free_char(mnsh->path_command);
		waitpid(pid, &mnsh->exit_code, 0);
	}
}

void	execute_last_command(char **str, t_lst *mnsh, int i)
{
	pid_t	pid;

	(void)i;
	if (check_if_fork(str, mnsh) == NOT_FOUND)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_printf_fd(2, "fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			if (mnsh->prev_fd[0] != 0)
			{
				dup2(mnsh->prev_fd[0], STDIN_FILENO);
				close(mnsh->prev_fd[0]);
			}
			else
			{
				dup2(mnsh->prev_fd[1], STDOUT_FILENO);
				close(mnsh->prev_fd[1]);
			}
			if (mnsh->outfile)
				dup2(mnsh->file_fd[1], STDOUT_FILENO);
			close(mnsh->fd[0]);
			close(mnsh->fd[1]);
			close(mnsh->backup[0]);
			close(mnsh->backup[1]);
			if (check_commands(str, mnsh) == SUCCESS)
				exit(0);
			else if (execve(mnsh->path_command, str, mnsh->env_var) == -1)
				exit(1);
			free_tab(str);
			free_char(mnsh->path_command);
			exit(0);
		}
		waitpid(pid, &mnsh->exit_code, 0);
	}
	/* 	if (mnsh->path_command != NULL)
				free_char(mnsh->path_command); */
	close(mnsh->fd[0]);
	close(mnsh->fd[1]);
	dup2(mnsh->backup[0], STDIN_FILENO);
	close(mnsh->backup[0]);
	dup2(mnsh->backup[1], STDOUT_FILENO);
	close(mnsh->backup[1]);
}

int	check_infile_outfile(t_lst *mnsh)
{
	mnsh->backup[0] = dup(STDIN_FILENO);
	mnsh->backup[1] = dup(STDOUT_FILENO);
	if (mnsh->infile)
	{
		mnsh->file_fd[0] = open(mnsh->infile, O_RDONLY);
		if (mnsh->file_fd[0] == -1)
		{
			ft_printf_fd(2, "minishell: %s: No such file or directory\n",
				mnsh->infile);
			return (ERROR);
		}
		dup2(mnsh->file_fd[0], STDIN_FILENO);
	}
	if (mnsh->outfile)
	{
		mnsh->file_fd[1] = open(mnsh->outfile, O_RDWR | O_CREAT | O_TRUNC,
				0640);
		dup2(mnsh->file_fd[1], STDOUT_FILENO);
	}
	return (SUCCESS);
}

int	exec_pipe(char **str, t_lst *mnsh)
{
	int		i;
	char	**tmp;

	i = 0;
	// add infile and outfile support
	if (check_infile_outfile(mnsh) == ERROR)
		return (ERROR);
	//mnsh->pipe_count = count_pipe(str);
	handle_sig(2);
	while (str[i])
	{
		tmp = ft_split(str[i], ' ');
		if (i != 0)
			mnsh->prev_fd[0] = mnsh->fd[0];
		if (i != mnsh->pipe_count - 1)
			pipe(mnsh->fd);
		if (!str[i + 1])
			execute_last_command(tmp, mnsh, i);
		else
			piping(tmp, mnsh, i);
		if (tmp != NULL)
			free_tab(tmp);
		i++;
	}
	waitpid(-1, &mnsh->exit_code, 0);
	return (SUCCESS);
}
