/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/20 14:27:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    input_reader(t_cli *cli)
{
    cli->input = readline(BRED "[~] " CRESET "MINISHELL $ > ");
	if (!cli->input)
	{
		free_char(cli->input);
		global_free(cli->args, cli->commands);
		free_cli(cli);
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	ft_printf_fd(cli->args->history_fd, "%s\n", cli->input);
	add_history(cli->input);
}