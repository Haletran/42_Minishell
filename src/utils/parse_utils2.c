/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:18:40 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/03 13:06:03 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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