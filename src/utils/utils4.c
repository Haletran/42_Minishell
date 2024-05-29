/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:01:45 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/29 14:28:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_file(char *name, t_cli *cli)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		execve("/bin/rm", (char *[]){"rm", "-rf", name, NULL},
			cli->mnsh->env_var);
		close(cli->mnsh->heredoc_fd);
		close(cli->mnsh->heredoc_backup_fd);
		exit(1);
	}
}

void	close_fds(void)
{
	int	i;

	i = 4;
	while (i <= 1023)
	{
		close(i);
		i++;
	}
}

void	print_error(int i, char *str)
{
	if (i == NOT_FOUND)
		ft_printf_fd(2, CRESET "minishell: %s: command not found\n", str);
	else if (i == FORK_FAILED)
		ft_printf_fd(2, CRESET "fork failed\n");
	else if (i == NO_FILE)
		ft_printf_fd(2, "%s: No such file or directory\n", str);
	else if (i == IS_DIRECTORY)
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
}

int	gate_or(int i)
{
	if (i == 0)
		return (1);
	else
		return (0);
}