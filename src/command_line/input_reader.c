/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/27 09:03:20 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_input(t_cli *cli)
{
	int	code;

	if (cli->mnsh->ctrl_c == 1)
		code = 130;
	else
		code = cli->mnsh->exit_code;
	cli->input = free_char(cli->input);
	ft_printf_fd(1, "exit\n");
	ft_exitcode(cli, code);
}

void	input_reader(t_cli *cli)
{
	char	*input_trim;

	if (cli->av != NULL)
		cli->input = ft_strdup(cli->av);
	else
		cli->input = readline(BRED "[~] " CRESET "MINISHELL > ");
	if (g_var == 2)
	{
		cli->mnsh->exit_code = 130;
		cli->mnsh->ctrl_c = 1;
		g_var = 0;
	}
	if (!cli->input)
		exit_input(cli);
	if (ft_strlen(cli->input) != 0)
	{
		input_trim = ft_strtrim(cli->input, " ");
		cli->input = free_char(cli->input);
		cli->input = ft_strdup(input_trim);
		input_trim = free_char(input_trim);
	}
	if (!cli->input)
		exit_input(cli);
	if (cli->input)
		add_history(cli->input);
}
