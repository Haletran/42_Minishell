/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 20:00:15 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	ouvrir les fds
//	deniere commande sortie standard
// 	sinon redirection
// 	exec avec boucle


//standard input
//infile 
// heredoc

void piping(char **str, t_lst *args, int i)
{
	pid_t pid;

	(void)i;
	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (i != 0) {
			dup2(args->prev_fd[0], STDIN_FILENO);
			close(args->prev_fd[0]);
		}
		if (i != args->pipe_count - 1) {
			dup2(args->fd[1], STDOUT_FILENO);
			close(args->fd[1]);
		}
		close(args->fd[0]);
		if (execve(args->path_command, str, args->env_var) == -1)
			ft_printf_fd(2, "execve failed\n");
		exit(0);
	}
}

void execute_last_command(char **str, t_lst *args, int i)
{
	pid_t pid;

	(void)i;
	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(args->prev_fd[0], STDIN_FILENO);
		close(args->prev_fd[0]);
		close(args->fd[1]);
		if (execve(args->path_command, str, args->env_var) == -1)
			ft_printf_fd(2, "execve failed\n");
		exit(0);
	}
	waitpid(-1, &args->exit_code, 0);
	close(args->fd[0]);
	close(args->fd[1]);
}


int exec_pipe(char **str, t_lst *args)
{
	int i;

	dup2(STDIN_FILENO, args->backup[0]);
	dup2(STDOUT_FILENO, args->backup[1]);
	i = 0;
	args->pipe_count = count_pipe(str);
	while (str[i])
	{
		char **tmp = ft_split(str[i], ' ');
		args->path_command = check_path(tmp, args, 0);
		if (i != 0)
			args->prev_fd[0] = args->fd[0];
		if (i != args->pipe_count - 1)
			pipe(args->fd);
		if (!str[i + 1])
			execute_last_command(tmp, args, i);
		else
			piping(tmp, args, i);
		i++;
	}
	return (0);
}

