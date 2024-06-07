/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:40:58 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/27 12:44:44 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	semi_colon_rules(t_cli *cli, t_token *token)
{
	if (token->prev == NULL)
		syntax_error(cli, ";");
	else if (token->prev->type == CONTROLE_OPERATOR)
		syntax_error(cli, ";");
	else if (token->prev->type == REDIRECTION_OPERATOR)
		syntax_error(cli, ";");
	else if (token->prev->type == KEYWORD)
		syntax_error(cli, ";");
}

void	pipe_rules(t_cli *cli, t_token *token)
{
	if (token->prev == NULL)
		syntax_error(cli, "|");
	else if (token->prev->type == CONTROLE_OPERATOR)
		syntax_error(cli, "|");
	else if (token->prev->type == REDIRECTION_OPERATOR)
		syntax_error(cli, "|");
	else if (token->prev->type == KEYWORD)
		syntax_error(cli, "|");
	else if (token->next == NULL)
		syntax_error(cli, "|");
}

void	control_rules(t_cli *cli, t_token *token)
{
	if (token->token[0] == ';')
		semi_colon_rules(cli, token);
	else if (token->token[0] == '|')
		pipe_rules(cli, token);
	// else if (token->token[0] == '&')
	//	and_rules(cli, token);
	// else if (token->token[0] == '(')
	//	open_bracket_rules(cli, token);
	// else if (token->token[0] == ')')
	//	close_bracket_rules(cli, token);
	// else
	//    syntax_error(cli, token->token);
}
