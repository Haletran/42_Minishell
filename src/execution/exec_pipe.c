/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/20 11:38:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	piping(char **str, t_lst *args, char *full_path, int *prev, int fd[2])
{
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(*prev, STDIN_FILENO);
		close(*prev);
		if (execve(full_path, str, args->env_var) == -1)
		{
			perror(full_path);
			exit(127);
		}
	}
	close(fd[1]);
	close(*prev);
	*prev = fd[0];
	signal(SIGINT, sig_command_is_running);
	return (0);
}

int	test_exec(char **str, t_lst **args, int *prev, int fd[2])
{
	char	*full_path;
	char	*tmp;
	int		i;

	full_path = NULL;
	i = 0;
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
			return (1);
	}
	piping(str, *args, full_path, prev, fd);
	return (0);
}

int	exec_pipe(char **str, t_lst *args)
{
	int		fd[2];
	int		i;
	char	**tab;
	int		prev;

	i = 0;
	prev = dup(STDIN_FILENO);
	while (str[i])
	{
		tab = ft_split(str[i], ' ');
		test_exec(tab, &args, &prev, fd);
		free_tab(tab);
		tab = NULL;
		i++;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	// close(prev);
	return (0);
}
