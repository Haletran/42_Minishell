/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:01:45 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/14 12:05:29 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void delete_file(char *name, t_cli *cli)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        exit(1);
    else if (pid == 0)
    {
        execve("/bin/rm", (char *[]){"rm", "-rf", name, NULL}, cli->mnsh->env_var);
        close(cli->mnsh->heredoc_fd);
        exit (1);
    }
}