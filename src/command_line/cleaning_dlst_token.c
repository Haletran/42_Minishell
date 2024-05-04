/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_dlst_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:50:50 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 12:28:28 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_cli *cli)
{
	t_token	*tmp;

	tmp = cli->token;
	while (tmp != NULL)
	{
		if ((tmp->type == QUOTE || tmp->type == DQUOTE) && tmp->prev != NULL)
		{
			tmp = tmp->prev;
			delete_node_token(&cli->token, tmp->next);
		}
		else if ((tmp->type == QUOTE || tmp->type == DQUOTE)
			&& tmp->next != NULL)
		{
			tmp = tmp->next;
			delete_node_token(&cli->token, tmp->prev);
		}
		else
			tmp = tmp->next;
	}
}

void	glue_quotes(t_cli *cli)
{
	t_token	*tmp;

	tmp = cli->token;
	while (tmp != NULL)
	{
		if ((tmp->type == IMMUTABLE && tmp->next->type == IMMUTABLE)
			|| (tmp->type == FREEZE && tmp->next->type == FREEZE))
		{
			tmp->token = ft_strjoin_f(tmp->token, tmp->next->token);
			delete_node_token(&cli->token, tmp->next);
		}
		else
			tmp = tmp->next;
	}
	tmp = cli->token;
	while (tmp != NULL)
	{
		if (tmp->type == IMMUTABLE || tmp->type == FREEZE)
			tmp->type = ARGUMENT;
		tmp = tmp->next;
	}
	reindex_token_list(cli);
}

void	cleaning_token_list(t_cli *cli)
{
	t_token			*tmp;
	unsigned int	i;

	i = -1;
	tmp = cli->token;
	while ((++i != cli->n_token) && (tmp != NULL))
	{
		if (ft_strcmp(tmp->token, " ") == 0 && tmp->type != IMMUTABLE
			&& tmp->type != FREEZE)
		{
			tmp = tmp->next;
			delete_node_token(&cli->token, tmp->prev);
		}
		else if (ft_strcmp(tmp->token, "\n") == 0 && tmp->type != IMMUTABLE
			&& tmp->type != FREEZE)
		{
			tmp = tmp->prev;
			delete_node_token(&cli->token, tmp->next);
		}
		else
			tmp = tmp->next;
	}
	reindex_token_list(cli);
}
