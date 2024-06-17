/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:18:40 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/17 11:41:30 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_census(t_token *tok, t_cli *cli)
{
	(void)cli;
	if (tok->prev == NULL || tok->prev->type == CONTROLE_OPERATOR)
		return (COMMAND);
	else if (tok->prev->type == DELIMITER)
		return (COMMAND);
	else if (tok->prev->prev != NULL)
		if (tok->prev->prev->type == REDIRECTION_OPERATOR)
			return (COMMAND);
	// to fix error
	return (ARGUMENT);
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
