/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:44:53 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/20 11:17:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_parsing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str, "./", 2))
		{
			if (access(str, F_OK) == -1)
			{
				print_error(NO_FILE, str);
				exit(127);
			}
			else if (access(str, X_OK) == -1)
			{
				ft_printf_fd(2, "%s: Permission denied\n", str);
				exit(126);
			}
			else
				str = ft_strtrim(ft_strrchr(str, '/'), "/");
		}
		i++;
	}
	return (str);
}

int	check_path_parsing(t_cli *cli)
{
	if (opendir(cli->com->command[0]) == NULL)
	{
		if (access(cli->com->command[0], F_OK | R_OK) != -1)
			return (SUCCESS);
		if (errno == EACCES)
		{
			print_error(PERMISSION_DENIED, cli->com->command[0]);
			cli->mnsh->exit_code = 126;
		}
		else
		{
			print_error(NO_FILE, cli->com->command[0]);
			cli->mnsh->exit_code = 127;
		}
	}
	else
	{
		print_error(IS_DIRECTORY, cli->com->command[0]);
		cli->mnsh->exit_code = 126;
	}
	return (ERROR);
}

void	update_command(t_cli *cli)
{
	cli->com->env_path = free_char(cli->com->env_path);
	cli->com->env_path = ft_strdup(cli->com->command[0]);
	free_tab(cli->com->command);
	cli->com->command = ft_calloc(2, ft_strlen(cli->com->env_path));
	cli->com->command[0] = check_parsing(cli->com->env_path);
	cli->com->command[1] = NULL;
}

int	parsing_check(t_cli *cli)
{
	if (cli->com->command == NULL)
		return (ERROR);
	if (!ft_strncmp(cli->com->command[0], "./", 2))
	{
		if (check_path_parsing(cli) == SUCCESS)
		{
			update_command(cli);
			return (SUCCESS);
		}
		else
			return (ERROR);
	}
	else if (!ft_strncmp(cli->com->command[0], "/", 1))
	{
		if (check_path_parsing(cli) == SUCCESS)
		{
			cli->com->env_path = ft_strdup(cli->com->command[0]);
			cli->com->command[0] = ft_strdup(ft_strcpy(cli->com->command[0],
						cli->com->env_path));
			return (SUCCESS);
		}
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int	get_nb_commands(t_com *com)
{
	int	nb_commands;

	nb_commands = 0;
	while (com)
	{
		nb_commands++;
		com = com->next;
	}
	return (nb_commands);
}
