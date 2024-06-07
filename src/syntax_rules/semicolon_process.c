/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:20:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/16 15:32:25 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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