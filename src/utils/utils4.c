/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:01:45 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/18 15:50:13 by bapasqui         ###   ########.fr       */
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

	i = 3;
	while (i <= 1024)
	{
		close(i);
		i++;
	}
}

void	print_error(int i, char *str)
{
	if (i == NOT_FOUND)
		ft_printf_fd(2, "minishell: %s: command not found\n", str);
	else if (i == FORK_FAILED)
		ft_printf_fd(2, CRESET "fork failed\n");
	else if (i == NO_FILE)
		ft_printf_fd(2, "%s: No such file or directory\n", str);
	else if (i == IS_DIRECTORY)
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
	else if (i == PERMISSION_DENIED)
		ft_printf_fd(2, "minishell: %s: Permission denied\n", str);
	else if (i == -50)
		ft_printf_fd(2, "minishell: quotes not closed\n");
}

int	gate_or(int i)
{
	if (i == 0)
		return (1);
	else
		return (0);
}

int	get_exit_code(t_lst *mnsh)
{
	if (WIFEXITED(mnsh->exit_code))
		return (mnsh->exit_code = WEXITSTATUS(mnsh->exit_code));
	else if (WIFSIGNALED(mnsh->exit_code))
		return (mnsh->exit_code = WTERMSIG(mnsh->exit_code) + 128);
	else if (WIFSTOPPED(mnsh->exit_code))
		return (mnsh->exit_code = WSTOPSIG(mnsh->exit_code));
	return (0);
}
