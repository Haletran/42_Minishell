/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 07:54:21 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/30 17:36:39 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (ft_unset(str, &cli->mnsh));
	else if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
		return (ft_cd(str, cli->mnsh));
	return (NOT_FOUND);
}

int	check_redir_not_fork(t_cli *cli, int *ret)
{
	if (nf_handle_redirection(&cli) == ERROR)
	{
		*ret = ERROR;
		return (ERROR);
	}
	return (SUCCESS);
}

int	check_if_fork(char **str, t_lst *mnsh, t_cli *cli)
{
	int	ret;

	ret = 0;
	if (cli->mnsh->pipe_count == 0)
	{
		if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
			if (check_redir_not_fork(cli, &ret) == SUCCESS)
				return (ft_export(mnsh, str));
		if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
			if (check_redir_not_fork(cli, &ret) == SUCCESS)
				return (ft_unset(str, &mnsh));
		if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
			if (check_redir_not_fork(cli, &ret) == SUCCESS)
				return (ft_exit(str[1], cli));
		if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
			if (check_redir_not_fork(cli, &ret) == SUCCESS)
				return (ft_cd(str, cli->mnsh));
	}
	if (ret != 0)
		return (SUCCESS);
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

int	sigpipe_checker(t_com *com)
{
	if (!com)
		return (ERROR);
	if (check_if_path_needed(com->command) == NOT_FOUND)
	{
		if (!com->env_path)
			return (ERROR);
		if (access(com->env_path, F_OK) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}
