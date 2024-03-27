/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/27 11:48:43 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	ouvrir les fds
//	deniere commande sortie standard
// 	sinon redirection
// 	exec avec boucle
//

void piping(char **str, t_lst **args)
{
    pid_t pid;
    int back = 0;
    int pipefd[2];

    signal(CTRL_C, sig_command_is_running);
    signal(CTRL_BACKSLACH, sig_ctrl_back);

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // parent
    {
        close(pipefd[0]);
        dup2(back, 0);
        dup2(pipefd[1], 1);
        close(pipefd[1]);

        if (execve((*args)->path_command, str, (*args)->env_var) == -1)
        {
            perror((*args)->path_command);
            g_value = 127;
            free_tab(str);
            exit(127);
        }
    }
    else // child
    {
        close(pipefd[1]);
        back = pipefd[0];
    }
}

int get_path(char **str, t_lst **args)
{
    char *full_path = NULL;
    char *tmp;
    int i = 0;

    if (ft_strchr(str[i], '/'))
    {
        if (access(str[i], F_OK) == 0)
        {
            full_path = str[i];
            tmp = ft_strrchr(str[i], '/');
            str[i] = ft_strdup(tmp);
        }
        else
        {
            perror(str[i]);
            g_value = 127;
            return (127);
        }
    }
    else
    {
        full_path = check_path(str, *args, 0);
        if (full_path == NULL)
            return (ERROR);
    }
    (*args)->path_command = full_path;
    return (SUCCESS);
}

int exec_pipe(char **str, t_lst *args)
{
    int i = 0;
    char **tab;

    while (str[i])
    {
        tab = ft_split(str[i], ' ');
        if (get_path(tab, &args) == SUCCESS)
        {
            piping(tab, &args);
            free_tab(tab);
            free(args->path_command);
            tab = NULL;
            i++;
        }
        else
            return (ERROR);
    }
    waitpid(-1, &g_value, 0);
    waitpid(-1, &g_value, 0);
    return (0);
}

