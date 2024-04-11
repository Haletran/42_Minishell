/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/11 15:18:16 by bapasqui         ###   ########.fr       */
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
    else
    {
        if (i != args->pipe_count - 1) {
            close(args->fd[1]);
        }
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
		if (args->prev_fd[0] != 0)
			dup2(args->prev_fd[0], STDIN_FILENO);
		else 
			dup2(args->prev_fd[1], STDOUT_FILENO);
		close(args->fd[1]);
		if (execve(args->path_command, str, args->env_var) == -1)
			ft_printf_fd(2, "execve failed\n");
		exit(0);
	}
	waitpid(pid, &args->exit_code, 0);
	close(args->fd[0]);
	close(args->fd[1]);
	dup2(args->backup[0], STDIN_FILENO);
	dup2(args->backup[1], STDOUT_FILENO);
}


int exec_pipe(char **str, t_lst *args)
{
	int i;
	char **tmp;

	args->backup[0] = dup(STDIN_FILENO);
	args->backup[1] = dup(STDOUT_FILENO);
	i = 0;
	args->pipe_count = count_pipe(str);
	handle_sig(2);
	while (str[i])
	{
		tmp = ft_split(str[i], ' ');
		args->path_command = check_path(tmp, args, 0);
		if (!args->path_command)
			break;
		if (i != 0)
			args->prev_fd[0] = args->fd[0];
		if (i != args->pipe_count - 1)
			pipe(args->fd);
		if (!str[i + 1])
			execute_last_command(tmp, args, i);
		else
			piping(tmp, args, i);
		//free_char(args->path_command);
		//free_tab(tmp);
		i++;
	}
	free_tab(tmp);
	return (0);
}

