/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:39 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/12 11:52:37 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cli *cli)
{
	if (!cli->com->command)
		return (ERROR);
	if (ft_strlen(cli->com->command[1]) > 0)
	{
		if (cli->com->command[1][0] == '-')
		{
			cli->mnsh->exit_code = 125;
			ft_printf_fd(2, "env: invalid option -- '%c'\n",
				cli->com->command[1][1]);
			return(125);
		}
		ft_printf_fd(2, "env: '%s': No such file or directory\n",
			cli->com->command[1]);
		cli->mnsh->exit_code = 127;
		return (127);
	}
	else if (ft_strlen(cli->com->command[1]) == 0)
	{
		print_list_env("=", cli->mnsh);
		cli->mnsh->exit_code = 0;
	}
	return (0);
}
