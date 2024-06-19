/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:29:56 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/19 08:54:27 by bapasqui         ###   ########.fr       */
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

void	replace_last_space(t_token *tok)
{
	if (tok->next == NULL)
	{
		if (ft_strcmp(tok->token, " ") == 0)
		{
			free_char(tok->token);
			tok->token = ft_strdup("");
		}
	}
}
