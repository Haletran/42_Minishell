/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/06 19:34:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
	//debug(cli, "parse");
	rulers(cli);
	tilde_expansion(cli);
	if (!varloc_creation(cli))
		return ;
	parameter_expansion(cli);
	glue_quotes(cli);
	remove_quotes(cli);
	cleaning_token_list(cli);
	create_command(cli);
	//debug(cli, "parse");
	return ;
}
