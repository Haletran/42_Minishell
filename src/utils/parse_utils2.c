/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:18:40 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/30 22:49:51 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int    command_census(t_token *tok, t_cli *cli)
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