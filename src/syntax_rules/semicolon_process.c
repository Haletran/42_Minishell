/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:20:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 15:46:39 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	semi_colon_process(t_cli *cli, t_token *token)
{
	if (token->prev == NULL)
		syntax_error(cli, ";");
	else if (token->prev->type == CONTROLE_OPERATOR)
		syntax_error(cli, ";");
	else if (token->prev->type == REDIRECTION_OPERATOR)
		syntax_error(cli, ";");
	else if (token->prev->type == KEYWORD)
		syntax_error(cli, ";");