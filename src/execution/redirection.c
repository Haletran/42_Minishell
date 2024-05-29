/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:21:24 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/29 13:54:31 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_infile(t_cli *cli)
{
    int fd;
    int i;

    if (cli == NULL || cli->mnsh == NULL)
        return (ERROR);

    i = 0;
    while (cli->mnsh->infile[i])
    {
        if (!cli->mnsh->infile[i + 1])
        {
            cli->mnsh->infile_fd = open(&cli->mnsh->infile[i], O_RDONLY, 0644);
            if (cli->mnsh->infile_fd == -1)
            {
                ft_printf_fd(2, "minishell: %s: %s\n", cli->mnsh->infile[i], strerror(errno));
                return (ERROR);
            }
            close(cli->mnsh->infile_fd);
        }
        if (cli->mnsh->infile[i])
        {
            fd = open(&cli->mnsh->infile[i], O_RDONLY, 0644);
            if (fd == -1)
            {
                ft_printf_fd(2, "minishell: %s: %s\n", cli->mnsh->infile[i], strerror(errno));
                return (ERROR);
            }
            close(fd);
        }
        i++;
    }
    return (SUCCESS);
}