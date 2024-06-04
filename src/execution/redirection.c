/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:21:24 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/03 13:04:53 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_outfile(t_cli *cli)
{
	t_com *com;
	int fd;
	int i = 0;
	com = cli->com;

	if (!com->redirection_out)
		return (ERROR);
	while (com->redirection_out[i])
	{
		if (!com->redirection_out[i + 1])
		{
			if (access(com->redirection_out[i], F_OK) != -1)
				cli->mnsh->outfile_fd = open(com->redirection_out[i], O_RDWR | O_TRUNC, 0640);
			else 
				cli->mnsh->outfile_fd = open(com->redirection_out[i], O_RDWR | O_TRUNC | O_CREAT, 0640);
			break;
		}
		fd = open(com->redirection_out[i], O_RDWR | O_TRUNC | O_CREAT, 0640);
		close(fd);
		i++;
	}
    if (cli->mnsh->outfile_fd == -1)
    {
        if (errno == ENOENT)
        {
		    ft_printf_fd(2, "minishell: No such file or directory \n");
        	cli->mnsh->exit_code = 0;
		}
		else
		{
            ft_printf_fd(2, "minishell: Permission denied \n");
        	cli->mnsh->exit_code = 1;
		}
		return (ERROR);
    }
	return (SUCCESS);
}

int handle_infile(t_cli *cli)
{
	t_com *com;
	int fd;
	int i = 0;
	com = cli->com;

	if (!com->redirection_in)
		return (ERROR);
	while (com->redirection_in[i])
	{
		printf("asd\n");
		if (!com->redirection_in[i + 1])
		{
			cli->mnsh->infile_fd = open(com->redirection_in[i], O_RDWR | O_TRUNC , 0640);
			break;
		}
		fd = open(com->redirection_in[i], O_RDWR | O_TRUNC , 0640);
		close(fd);
		i++;
	}
    if (cli->mnsh->infile_fd == -1)
    {
        if (errno == ENOENT)
        {
		    ft_printf_fd(2, "minishell: No such file or directory \n");
        	cli->mnsh->exit_code = 0;
		}
		else
		{
            ft_printf_fd(2, "minishell: Permission denied \n");
        	cli->mnsh->exit_code = 1;
		}
		return (ERROR);
    }
	return (SUCCESS);
}
