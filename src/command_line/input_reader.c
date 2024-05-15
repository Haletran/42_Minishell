/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/11 12:08:39 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	input_reader(t_cli *cli)
{
	char	*input_trim;

	cli->input = readline(BRED "[~] " CRESET "MINISHELL $ > ");
	if (!cli->input)
	{
		freeway(cli);
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	if (ft_strlen(cli->input) != 0)
	{
	input_trim = ft_strtrim(cli->input, " ");
	free_char(cli->input);
	cli->input = ft_strdup(input_trim);
	free_char(input_trim);
	}
	if (!cli->input)
	{
		freeway(cli);
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	ft_printf_fd(cli->mnsh->history_fd, "%s\n", cli->input);
	add_history(cli->input);
}