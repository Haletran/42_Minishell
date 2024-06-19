/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:51:31 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/19 12:36:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
	rulers(cli);
	tilde_expansion(cli);
	if (!varloc_creation(cli))
		return (ERROR);
	parameter_expansion(cli);
	glue_quotes(cli);
	remove_quotes(cli);
	cleaning_token_list(cli);
	create_command(cli);
	return (SUCCESS);
}
