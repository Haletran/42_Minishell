/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:37:14 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reindex_token_list(t_cli *cli)
{
	t_token	*tmp;
	int		i;

	tmp = cli->token;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
	cli->n_token = i;
}

void	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
	while ((cli->n_quote & 1 || cli->n_dquote & 1) == 1)
	{
		free(cli->input);
		cli->input = readline("> ");
		split_into_token(cli);
	}
	cleaning_token_list(cli);
	rulers(cli);
	tilde_expansion(cli);
	if (!varloc_creation(cli))
		return ;
	parameter_expansion(cli);
	glue_quotes(cli);
	remove_quotes(cli);
	create_command(cli);
	print_all_in_cli(cli);
	print_all_com(cli->com);
}
