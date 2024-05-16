/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/16 15:33:26 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_input(t_cli *cli)
{
	freeway(cli);
	ft_printf_fd(1, "exit\n");
	exit(0);
}

void	input_reader(t_cli *cli)
{
	char	*input_trim;

	cli->input = readline(BRED "[~] " CRESET "MINISHELL $ > ");
	if (!cli->input)
		exit_input(cli);
	if (ft_strlen(cli->input) != 0)
	{
		input_trim = ft_strtrim(cli->input, " ");
		free_char(cli->input);
		cli->input = ft_strdup(input_trim);
		free_char(input_trim);
	}
	if (!cli->input)
		exit_input(cli);
	ft_printf_fd(cli->mnsh->history_fd, "%s\n", cli->input);
	add_history(cli->input);
}
