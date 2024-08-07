/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   census_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:18:40 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/08 13:35:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	gate_or(int i)
{
	if (i == 0)
		return (1);
	else
		return (0);
}

t_token_type	add_flag(t_cli *cli, t_token_type type)
{
	if (type == QUOTE)
	{
		cli->flag_quote = gate_or(cli->flag_quote);
		cli->n_quote++;
	}
	else if (type == DQUOTE)
	{
		cli->flag_dquote = gate_or(cli->flag_dquote);
		cli->n_dquote++;
	}
	else if (type == HEREDOC)
		cli->heredoc = 1;
	else if (type == DELIMITER)
		cli->heredoc = 0;
	return (type);
}

int	get_last_token_command(t_token *tok)
{
	while (tok->prev != NULL)
	{
		tok = tok->prev;
		if (tok->type == COMMAND)
			return (1);
		if (tok->type == CONTROLE_OPERATOR)
			break ;
	}
	return (0);
}

int	command_census(t_token *tok, t_cli *cli)
{
	(void)cli;
	if (tok->prev == NULL || tok->prev->type == CONTROLE_OPERATOR)
		return (COMMAND);
	else if (tok->prev->prev != NULL && tok->prev->prev->type == HEREDOC)
		return (COMMAND);
	else if (tok->prev->type == 13)
		if (get_last_token_command(tok) == 0)
			return (COMMAND);
	if (tok->prev != NULL)
		if (tok->prev->type == COMMAND && tok->prev->token[0] == 0)
			return (COMMAND);
	return (ARGUMENT);
}

t_token_type	quote_n_heredoc_census(char *token, t_cli *cli)
{
	if (ft_isthis("'", token[0]) > 0 && cli->flag_dquote != 1)
		return (add_flag(cli, QUOTE));
	else if (ft_isthis("\"", token[0]) > 0 && cli->flag_quote != 1)
		return (add_flag(cli, DQUOTE));
	else if (cli->flag_quote & 1)
		return (IMMUTABLE);
	else if (cli->flag_dquote & 1)
		return (FREEZE);
	if (token[0] == '<' && token[1] == '<')
		return (add_flag(cli, HEREDOC));
	if (cli->heredoc == 1 && ft_isthis(" \t\n", token[0]) == 0)
	{
		if (ft_lencmparray(token, cli->control) > 0)
			return (CONTROLE_OPERATOR);
		else if (ft_lencmparray(token, cli->redirect) > 0)
			return (REDIRECTION_OPERATOR);
		else
			return (add_flag(cli, DELIMITER));
	}
	return (REDIRECTION_OPERATOR);
}
