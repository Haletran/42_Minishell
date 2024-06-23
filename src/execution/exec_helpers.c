/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:25:55 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/23 20:33:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void redirect_std(t_cli *cli)
{
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
}

void wait_process(void)
{
	while (waitpid(-1, NULL, 0) > 0)
		;
}
