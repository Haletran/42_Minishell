/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:29:56 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/01 15:14:32 by bapasqui         ###   ########.fr       */
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
		if (tmp->type != FREEZE && tmp->type != IMMUTABLE)
		{
			tmp->type = token_type_rediscovery(tmp, cli);
			tmp->index = i;
		}
		tmp = tmp->next;
		i++;
	}
	cli->n_token = i;
}

// void	replace_last_space(t_token *tok)
// {
// 	if (tok->next == NULL)
// 	{
// 		if (ft_strcmp(tok->token, " ") == 0)
// 		{
// 			free_char(tok->token);
// 			tok->token = ft_strdup(" ");
// 		}
// 	}
// }

int	replace_empty_quote(t_cli *cli, t_token *tok)
{
	if (tok->next == NULL)
		return (0);
	if ((tok->type == QUOTE && tok->next->type == QUOTE) || (tok->type == DQUOTE
			&& tok->next->type == DQUOTE))
	{
		tok = tok->next;
		free_char(tok->token);
		tok->token = ft_strdup("");
		tok->type = token_type_rediscovery(tok, cli);
		return (1);
	}
	return (0);
}

t_token	*delete_token_empty(t_cli *cli, t_token *tok)
{
	if (ft_strcmp(tok->token, "") == 0)
	{
		if (tok->next == NULL && tok->prev == NULL)
		{
			delete_node_token(&cli->token, tok);
			return (NULL);
		}
		else if (tok->prev == NULL)
		{
			tok = tok->next;
			delete_node_token(&cli->token, tok->prev);
			return (tok);
		}
		else if (tok->next == NULL)
		{
			tok = tok->prev;
			delete_node_token(&cli->token, tok->next);
			return (tok);
		}
	}
	return (tok->next);
}
