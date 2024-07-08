/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:40:58 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/08 12:16:54 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	semi_colon_rules(t_cli *cli, t_token *token)
{
	t_token	*tmp;

	tmp = prev_selector(token);
	if (ft_strcmp(token->token, ";;") == 0)
		syntax_error(cli, ";;");
	else if (ft_strcmp(token->token, ";;&") == 0)
		syntax_error(cli, ";;&");
	else if (ft_strcmp(token->token, ";&") == 0)
		syntax_error(cli, ";&");
	else if (tmp == NULL)
		syntax_error(cli, ";");
	else if (tmp->type == CONTROLE_OPERATOR)
		syntax_error(cli, ";");
	else if (tmp->type == REDIRECTION_OPERATOR)
		syntax_error(cli, ";");
	else if (tmp->type == KEYWORD)
		syntax_error(cli, ";");
}

void	pipe_rules(t_cli *cli, t_token *token)
{
	t_token	*prev_tmp;
	t_token	*next_tmp;

	prev_tmp = prev_selector(token);
	next_tmp = next_selector(token);
	if (prev_tmp == NULL || next_tmp == NULL)
		syntax_error(cli, "|");
	else if (prev_tmp->type == CONTROLE_OPERATOR)
		syntax_error(cli, "|");
	else if (prev_tmp->type == REDIRECTION_OPERATOR)
		syntax_error(cli, "|");
	else if (prev_tmp->type == KEYWORD)
		syntax_error(cli, "|");
	else if (prev_tmp->next == NULL)
		syntax_error(cli, "|");
}

void	control_rules(t_cli *cli, t_token *token)
{
	if (ft_strcmp(token->token, "||") == 0)
		syntax_error(cli, "||");
	else if (ft_strcmp(token->token, "|&") == 0)
		syntax_error(cli, "|&");
	else if (ft_strcmp(token->token, "&&") == 0)
		syntax_error(cli, "&&");
	else if (token->token[0] == ';')
		semi_colon_rules(cli, token);
	else if (token->token[0] == '|')
		pipe_rules(cli, token);
}
