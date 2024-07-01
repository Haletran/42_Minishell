/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:51:31 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/01 12:07:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_organiser(t_cli *cli)
{
	int	err;

	if (cli->process_com == 1)
	{
		err = cli->mnsh->exit_code;
		freeway(cli);
		exit(err);
	}
	input_reader(cli);
	if (cli->av != NULL)
		cli->process_com = 1;
	split_into_token(cli);
	rulers(cli);
	tilde_expansion(cli);
	parameter_expansion(cli);
	glue_quotes(cli);
	remove_quotes(cli);
	cleaning_token_list(cli);
	create_command(cli);
	return (SUCCESS);
}
