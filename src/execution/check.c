/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 07:54:21 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/17 12:13:34 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	choose(t_cli *cli)
{
/* 	if (!cli->com)
		rl_on_new_line();
	else */
		exec_pipe(cli);
	return ;
}

/**
 * @brief Associate commands to built-ins if needed
 *
 * @param str
 * @param mnsh
 * @return int (true / false)
 */
int	check_commands(char **str, t_cli *cli)
{
	if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
		return (ft_export(cli->mnsh, str));
	else if (!ft_strncmp(str[0], "pwd", 3) && ft_strlen(str[0]) == 3)
		return (pwd(cli->mnsh, cli));
	else if ((!ft_strncmp(str[0], "echo", 4) && ft_strlen(str[0]) == 4)
		|| (!ft_strncmp(str[0], "e\"ch\"o", 5) && ft_strlen(str[0]) == 6))
		return (ft_echo(str, cli->mnsh, cli));
	else if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (ft_env(cli));
	else if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
		return (ft_exit(str[1], cli));
	return (NOT_FOUND);
}

int	check_if_fork(char **str, t_lst *mnsh, t_cli *cli)
{
	if (cli->mnsh->pipe_count == 0)
	{
		if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
			return (ft_export(mnsh, str));
		else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
			return (ft_unset(str, &mnsh));
		else if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
			return (ft_exit(str[1], cli));
		else if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
			return (ft_cd(str, cli->mnsh));
	}
	return (NOT_FOUND);
}

int	check_if_path_needed(char **str)
{
	if (!ft_strncmp(str[0], "pwd", 3) && ft_strlen(str[0]) == 3)
		return (SUCCESS);
	else if ((!ft_strncmp(str[0], "echo", 4) && ft_strlen(str[0]) == 4)
		|| (!ft_strncmp(str[0], "e\"ch\"o", 5) && ft_strlen(str[0]) == 6))
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "<<", 2) && ft_strlen(str[0]) == 2)
		return (SUCCESS);
	return (NOT_FOUND);
}
