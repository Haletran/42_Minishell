/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:38:15 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/01 14:54:19 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_process(int exit_code, t_cli *cli)
{
	if (cli->mnsh->outfile_check == 0)
		ft_printf_fd(1, EXIT_MSG);
	freeway(cli);
	return (exit_code);
}

void	ft_main_exit(t_cli *cli, long long exit_code)
{
	if (cli->mnsh->outfile_check == 0)
		ft_printf_fd(1, "exit\n");
	freeway(cli);
	exit(exit_code % 256);
}
