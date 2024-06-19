/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:47:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/19 09:33:06 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_error(t_cli **cli)
{
	t_com	*tmp;

	tmp = (*cli)->com;
	if (!tmp)
		return (ERROR);
	if (check_if_path_needed(tmp->command) == NOT_FOUND)
	{
		if (access(tmp->env_path, F_OK) == -1)
		{
			(*cli)->mnsh->exit_code = 127;
			print_error(NOT_FOUND, tmp->command[0]);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

void	fork_error(void)
{
	print_error(FORK_FAILED, NULL);
	exit(1);
}

void	piping(t_cli *cli, int count)
{
	pid_t	pid;

	pid = fork();
	(void)count;
	if (pid == -1)
		fork_error();
	else if (pid == 0)
	{
		redirection_error(cli);
		redirection_fd(cli);
		redirection_pipe(cli);
		if (check_commands(cli->com->command, cli) == NOT_FOUND)
		{
			if (execve(cli->com->env_path, cli->com->command,
					cli->mnsh->env_var) == -1)
				ft_exitcode(cli, cli->mnsh->exit_code);
		}
		if (check_if_builtin(cli->com->command[0]) == SUCCESS)
			ft_exitcode(cli, cli->mnsh->exit_code);
	}
	else
		redirection_parent(cli);
}

void	execute_last_command(t_cli *cli)
{
	pid_t	pid;

	if (check_if_fork(cli->com->command, cli->mnsh, cli) == NOT_FOUND)
	{
		pid = fork();
		if (pid == -1)
			fork_error();
		else if (pid == 0)
		{
			redirection_fd(cli);
			if (check_commands(cli->com->command, cli) == NOT_FOUND)
			{
				if (execve(cli->com->env_path, cli->com->command,
						cli->mnsh->env_var) == -1)
					ft_exitcode(cli, cli->mnsh->exit_code);
			}
			if (check_if_builtin(cli->com->command[0]) == SUCCESS)
				ft_exitcode(cli, cli->mnsh->exit_code);
		}
		else
			waitpid(pid, &cli->mnsh->exit_code, 0);
	}
	if (cli->mnsh->exit_code != 127 && check_if_forked(cli) == NOT_FOUND)
		cli->mnsh->exit_code = get_exit_code(cli->mnsh);
}
