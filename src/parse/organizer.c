/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:51:31 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/26 13:09:49 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
	rulers(cli);
	tilde_expansion(cli);
	// debug(cli, "before parameter_expansion");
	parameter_expansion(cli);
	// debug(cli, "after parameter_expansion");
	glue_quotes(cli);
	remove_quotes(cli);
	cleaning_token_list(cli);
	create_command(cli);
	// debug(cli, "after parsing_organiser");
	return (SUCCESS);
}
