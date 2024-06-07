/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/06/06 12:25:39 by bapasqui         ###   ########.fr       */
=======
/*   Updated: 2024/06/06 15:08:23 by bapasqui         ###   ########.fr       */
>>>>>>> 00a7aac (fix exec)
=======
/*   Updated: 2024/06/06 19:34:32 by bapasqui         ###   ########.fr       */
>>>>>>> 5258212 (test)
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
<<<<<<< HEAD
<<<<<<< HEAD
	debug(cli, "parse");
=======
	// debug(cli, "parse");
>>>>>>> 00a7aac (fix exec)
=======
	//debug(cli, "parse");
>>>>>>> 5258212 (test)
	rulers(cli);
	tilde_expansion(cli);
	if (!varloc_creation(cli))
		return ;
	parameter_expansion(cli);
	glue_quotes(cli);
	remove_quotes(cli);
	cleaning_token_list(cli);
	create_command(cli);
<<<<<<< HEAD
<<<<<<< HEAD
	debug(cli, "parse");
=======
	// debug(cli, "parse");
>>>>>>> 00a7aac (fix exec)
=======
	//debug(cli, "parse");
>>>>>>> 5258212 (test)
	return ;
}
