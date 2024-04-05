/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/05 15:56:04 by bapasqui         ###   ########.fr       */
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

void	piping(char **str, t_lst *args, int i, int *fd)
{
	//pid_t 	pid;
	(void)i;
	(void)fd;
	printf("piping : \n");
	exec_command(str, args, args->path_command);
}

void execute_last_command(char **str, t_lst *args, int i, int *fd)
{
	(void)i;
	(void)fd;
	printf("last command : \n");
	exec_command(str, args, args->path_command);
	return ;
}


int	exec_pipe(char **str, t_lst *args)
{
	int pipe_fd[2];
	int i;
	
	//dup2(STDIN_FILENO, args->backup[0]);
	//dup2(STDOUT_FILENO, args->backup[1]);
	//Need to have a backup of the standard input and output
	i = 0;
	char **tmp = ft_calloc(sizeof(char *), 1);
	while (str[i])
	{
		tmp = ft_split(str[i], ' ');
		// Have a clean command without args and one with args for execve
		// linked list with command - args - path
		args->path_command = check_path(tmp, args, 0);
		//printf("path : %s\n", args->path_command);
		if (!str[i + 1])
			execute_last_command(tmp, args, i, pipe_fd);
		else
			piping(tmp, args, i, pipe_fd);
		//free_tab(tmp);
		i++;
	}
	return (0);
}
