/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/05 02:18:58 by baptiste         ###   ########.fr       */
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
	(void)str;
	(void)args;
	(void)i;
	(void)fd;
	printf("piping : ");
	print_tab(str);
	
	

}

void execute_last_command(char **str, t_lst *args, int i, int *fd)
{
	(void)str;
	(void)args;
	(void)i;
	(void)fd;
	printf("last command : ");
	print_tab(str);

}


int	exec_pipe(char **str, t_lst *args)
{
	int pipe_fd[2];
	int i;


	//dup2(STDIN_FILENO, args->backup[0]);
	//dup2(STDOUT_FILENO, args->backup[1]);
	//Need to have a backup of the standard input and output
	i = 0;
	while (str[i])
	{
		// Have a clean command without args and one with args for execve
		// linked list with command - args - path
		args->path_command = check_path(str, args, i);
		if (!str[i + 1])
			execute_last_command(str, args, i, pipe_fd);
		else
			piping(str, args, i, pipe_fd);
		i++;
	}
	return (0);
}
