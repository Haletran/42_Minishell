/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:40:58 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/08 13:38:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	gt_rules(t_cli *cli, t_token *token)
{
	t_token	*tmp;

	tmp = next_selector(token);
	if (token == NULL || tmp == NULL)
		syntax_error(cli, "newline");
	else if (ft_strcmp(token->token, GREATER_THAN) == 0)
	{
		if (token->index == get_last_index(cli->token))
			syntax_error(cli, "newline");
		else if (tmp->type == 2 || tmp->type == 1)
			syntax_error(cli, tmp->token);
		else if (ft_strchr(tmp->token, '*') != 0)
			syntax_error(cli, tmp->token);
	}
	else if (ft_strcmp(token->token, DOUBLE_GREATER_THAN) == 0)
	{
		if (token->index == get_last_index(cli->token))
			syntax_error(cli, "newline");
		else if (tmp->type == 2 || tmp->type == 1)
			syntax_error(cli, tmp->token);
		else if (ft_strchr(tmp->token, '*') != 0)
			syntax_error(cli, tmp->token);
	}
}

void	lt_rules(t_cli *cli, t_token *token)
{
	t_token	*tmp;

	tmp = next_selector(token);
	if (token == NULL || tmp == NULL)
		syntax_error(cli, "newline");
	else if (ft_strcmp(token->token, LESS_THAN) == 0)
	{
		if (token->index == get_last_index(cli->token))
			syntax_error(cli, "newline");
		else if (tmp->type == 2 || tmp->type == 1)
			syntax_error(cli, tmp->token);
		else if (ft_strchr(tmp->token, '*') != 0)
			syntax_error(cli, tmp->token);
	}
	else if (ft_strcmp(token->token, DOUBLE_LESS_THAN) == 0)
	{
		if (token->index == get_last_index(cli->token))
			syntax_error(cli, "newline");
		else if (tmp->type == 2 || tmp->type == 1)
			syntax_error(cli, tmp->token);
		else if (ft_strchr(tmp->token, '*') != 0)
			syntax_error(cli, tmp->token);
	}
}

void	redirect_rules(t_cli *cli, t_token *token)
{
	if (token->token[0] == '<' && cli->rules_flag == 0)
		lt_rules(cli, token);
	else if (token->token[0] == '>' && cli->rules_flag == 0)
		gt_rules(cli, token);
	else if (token->next == NULL && cli->rules_flag == 0)
		syntax_error(cli, "newline 2");
	else
		return ;
}
