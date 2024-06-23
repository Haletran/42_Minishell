/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:51:31 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/23 20:01:33 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
	// debug(cli, "before Rulers");
	rulers(cli);
	tilde_expansion(cli);
	parameter_expansion(cli);
	// debug(cli, "after parameter_expansion");
	glue_quotes(cli);
	remove_quotes(cli);
	cleaning_token_list(cli);
	create_command(cli);
	// debug(cli, "after parsing_organiser");
	return (SUCCESS);
}
