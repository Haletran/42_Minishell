/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:39 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/27 23:31:36 by bapasqui         ###   ########.fr       */
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
			ft_printf_fd(2, ENV_INV_OPT,
				cli->com->command[1][1]);
			ft_printf_fd(2, ENV_HELP);
			return (125);
		}
		ft_printf_fd(2, ENV_NO_FILE,
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
