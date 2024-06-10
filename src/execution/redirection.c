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

int handle_redirection(t_cli **cli)
{
    t_redirection *red;

    red = (*cli)->com->redirection;
    while (red)
    {
        if (red->type == IN)
        {
	        if (handle_infile(red, (*cli)) == ERROR)
	    	    return (ERROR);
        }
        else if (red->type == OUT || red->type == APPEND_OUT)
	    {
            if (handle_outfile(red, (*cli)) == ERROR)
	    	    return (ERROR);
        }
        red = red->next;
    }
    return (SUCCESS);
}

int handle_error(int fd, t_cli *cli)
{
    if (errno == ENOENT)
    {
        ft_printf_fd(2, "minishell: No such file or directory\n");
        cli->mnsh->exit_code = 1;
        close(fd);
        return (ERROR);
    }
    else
    {
        ft_printf_fd(2, "minishell: Permission denied\n");
        cli->mnsh->exit_code = 1;
        close(fd);
        return (ERROR);
    }
    return (SUCCESS);
}

int handle_outfile(t_redirection *red, t_cli *cli)
{
    int fd;
    if (access(red->file, F_OK) != -1)
    {
        if (red->type == APPEND_OUT)
            fd = open(red->file, O_RDWR | O_APPEND, 0640);
        else
            fd = open(red->file, O_RDWR | O_TRUNC, 0640);
    }
    else
    {
        if (red->type == APPEND_OUT)
            fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0640);
        else
            fd = open(red->file, O_RDWR | O_CREAT, 0640);
    }
    if (fd == -1)
    {
        if (handle_error(fd, cli) == ERROR)
            return (ERROR);
    }
    if (!red->next)
    {
        cli->mnsh->outfile_fd = dup(fd);
        cli->mnsh->outfile_check = 1;
    }
    close(fd);
    return (SUCCESS);
}

int handle_infile(t_redirection *red, t_cli *cli)
{
    int fd;

    fd = open(red->file, O_RDONLY, 0640);
    if (fd == -1)
    {
        if (handle_error(fd, cli) == ERROR)
            return (ERROR);
    }
    if (!red->next)
    {
        cli->mnsh->infile_fd = dup(fd);
        cli->mnsh->infile_check = 1;
    }
    close(fd);
    return (SUCCESS);
}


