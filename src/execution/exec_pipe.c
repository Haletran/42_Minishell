/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 10:36:15 by bapasqui         ###   ########.fr       */
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

void	piping(char **str, t_lst *args, int i)
{
	pid_t 	pid;

	pid = fork();
	(void)i;
	if (pid == -1)
	{
		ft_printf_fd(2, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(args->fd[0], STDIN_FILENO);
		close(args->fd[0]);
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->fd[1]);
		if (execve(args->path_command, str, args->env_var) == -1)
			ft_printf_fd(2, "execve failed\n");
		//exit(1);
	}
	else
		printf("piping : %s\n", str[0]);
	//exec_command(str, args, args->path_command);
}
 
void execute_last_command(char **str, t_lst *args, int i)
{
	(void)i;
	(void)str;
	(void)args;
	pid_t 	pid;

	pid = fork();
	(void)i;
	if (pid == -1)
	{
		ft_printf_fd(2, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(args->fd[0], STDIN_FILENO);
		close(args->fd[0]);
/* 		dup2(args->fd[1], STDOUT_FILENO);
		close(args->fd[1]); */
		if (execve(args->path_command, str, args->env_var) == -1)
			ft_printf_fd(2, "execve failed\n");
		exit(1);
	}
	else
		printf("last command : %s\n", str[0]);
	//exec_command(str, args, args->path_command);
	return ;
}


int	exec_pipe(char **str, t_lst *args)
{
	int i;
	
	args->backup = malloc(sizeof(int) * 2);
	dup2(STDIN_FILENO, args->backup[0]);
	dup2(STDOUT_FILENO, args->backup[1]);
	//Need to have a backup of the standard input and output
	i = 0;
	char **tmp = ft_calloc(1, sizeof(char *));
	while (str[i])
	{
		tmp = ft_split(str[i], ' ');
		// Have a clean command without args and one with args for execve
		// linked list with command - args - path
		args->path_command = check_path(tmp, args, 0);
		pipe(args->fd);
		if (!str[i + 1])
			execute_last_command(tmp, args, i);
		else
			piping(tmp, args, i);
		//free_tab(tmp);
		i++;
	}
	free(args->backup);
	return (0);
}
