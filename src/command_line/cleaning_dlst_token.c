/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_dlst_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:50:50 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/15 01:08:25 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	// reindex_token_list(cli);
}

void	cleaning_token_list(t_cli *cli)
{
	t_token			*tmp;
	unsigned int	i;

	i = -1;
	tmp = cli->token;
	concat_no_space(cli);
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

void	concat_no_space(t_cli *cli)
{
	t_token	*tmp;

	tmp = cli->token;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			break ;
		if (ft_strcmp(tmp->token, " ") != 0 && tmp->next != NULL
			&& ft_strcmp(tmp->next->token, " ") != 0)
		{
			if ((tmp->type == COMMAND || tmp->type == ARGUMENT
					|| tmp->type == BUILTIN) && (tmp->next->type == COMMAND
					|| tmp->next->type == ARGUMENT
					|| tmp->next->type == BUILTIN))
			{
				tmp->token = ft_strjoin_f(tmp->token, tmp->next->token);
				delete_node_token(&cli->token, tmp->next);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	// reindex_token_list(cli);
}
