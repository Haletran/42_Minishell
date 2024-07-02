/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 11:00:33 by bapasqui         ###   ########.fr       */
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

static char	*swap_trim(char *input)
{
	char	*input_trim;

	if (ft_strlen(input) != 0)
	{
		input_trim = ft_strtrim(input, " ");
		if (!input_trim)
			return (NULL);
		input = free_char(input);
		input = ft_strdup(input_trim);
		if (!input)
			return (NULL);
		input_trim = free_char(input_trim);
	}
	return (input);
}

void	input_reader(t_cli *cli)
{
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
	cli->input = swap_trim(cli->input);
	if (!cli->input)
		exit_input(cli);
	if (cli->input)
		add_history(cli->input);
}
