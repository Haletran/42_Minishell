/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/20 14:24:26 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_command(t_cli *cli)
{
	t_token	*tmp;

	if (cli->token == NULL)
		return ;
	free(cli->input);
	cli->input = ft_calloc(1, sizeof(char));
	tmp = cli->token;
	while (tmp->next != NULL)
	{
		if (tmp->type != QUOTE)
			cli->input = ft_strjoin(cli->input, tmp->token);
		if (tmp->next != NULL)
			cli->input = ft_strjoin(cli->input, " ");
		tmp = tmp->next;
	}
	if (tmp->type != QUOTE)
		cli->input = ft_strjoin(cli->input, tmp->token);
}

void	glue_quotes(t_cli *cli)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = cli->token;
	while (tmp)
	{
		if (tmp->type == IMMUABLE)
		{
			delete_node_token(&cli->token, tmp->prev);
			tmp2 = tmp->next;
			while (tmp2)
			{
				if (tmp2->type == IMMUABLE)
				{
					tmp->token = ft_strjoin(tmp->token, tmp2->token);
					tmp->token = ft_strjoin(tmp->token, " ");
					delete_node_token(&cli->token, tmp2);
				}
				else
					break ;
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

void	parsing_organiser(t_cli *cli)
{
	input_reader(cli);
	split_into_token(cli);
	while ((cli->n_quote & 1) == 1)
	{
		free(cli->input);
		cli->input = readline("> ");
		split_into_token(cli);
	}
	print_all_in_cli(cli);
	tilde_expansion(cli);
	print_all_in_cli(cli);
	varloc_creation(cli);
	parameter_expansion(cli);
	create_command(cli);
	print_all_in_cli(cli);
}