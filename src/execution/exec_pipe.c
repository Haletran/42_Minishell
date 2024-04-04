/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/04 18:15:19 by bapasqui         ###   ########.fr       */
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

/* void	piping(char **str, t_lst **args)
{



} */



int	exec_pipe(char **str, t_lst *args)
{
	//int pipe_fd[2];
	int i;

	i = 0;
	while (str[i])
	{
		args->path_command = check_path(str, args, i);
		printf("path_command: %s\n", args->path_command);
		i++;
	}
	return (0);
}
