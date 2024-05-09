/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:01:11 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/09 19:03:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//? https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html

t_token_type	quote_n_heredoc_census(char *token, t_cli *cli)
{
	if (ft_isthis("\"", token[0]) > 0)
	{
		cli->n_dquote++;
		return (DQUOTE);
	}
	if (ft_isthis("'", token[0]) > 0)
	{
		cli->n_quote++;
		return (QUOTE);
	}
	if (token[0] == '<' && token[1] == '<')
	{
		cli->heredoc = 1;
		return (HEREDOC);
	}
	if (cli->heredoc == 1 && ft_isthis(" \t\n", token[0]) == 0)
	{
		cli->heredoc = 0;
		return (DELIMITER);
	}
	return (REDIRECTION_OPERATOR);
}

t_token_type	token_type_discovery(char *token, t_cli *cli)
{
	if (cli->heredoc == 1 && ft_isthis(" \t\n", token[0]) == 0)
		return (quote_n_heredoc_census(token, cli));
	if (ft_isthis("\"'<", token[0]) > 0)
		return (quote_n_heredoc_census(token, cli));
	if (cli->n_dquote & 1)
		return (FREEZE);
	if (cli->n_quote & 1)
		return (IMMUTABLE);
	if (ft_lencmparray(token, cli->redirect) > 0)
		return (REDIRECTION_OPERATOR);
	if (ft_lencmparray(token, cli->control) > 0)
		return (CONTROLE_OPERATOR);
	if (ft_lencmparray(token, cli->bracket) > 0)
		return (BRACKET);
	if (ft_lencmparray(token, cli->builtin) > 0)
		return (BUILTIN);
	if (ft_lencmparray(token, cli->keyword) > 0)
		return (KEYWORD);
	if ((cli->token == NULL || ft_iscontrol(get_token_from_index(cli->token,
				get_last_index(cli->token)), cli) > 0)
		&& (ft_strlen(token) > 0))
		return (COMMAND);
	return (ARGUMENT);
}

void	split_into_token(t_cli *cli)
{
	int		i;
	int		offset;
	char	*token_tmp;

	cli->n_token = get_last_index(cli->token) + 1;
	i = 0;
	cli->last_was_pipe = 0;
	while (cli->input[i] != 0)
	{
		if (ft_isthis("\n\t", cli->input[i]))
			i++;
		if (cli->input[i] == 0)
			break ;
		offset = ft_lenstrtype(cli->input + i, cli);
		if (ft_isthis(" '\"\t\n", cli->input[i]))
			offset++;
		if (offset == 0)
			offset = get_position_of_next_meta(cli->input + i);
		token_tmp = ft_substr(cli->input, i, offset);
		if (token_tmp == NULL)
			return ;
		insert_token_end(&cli->token, ft_strdup(token_tmp),
			token_type_discovery(token_tmp, cli), cli->n_token++);
		token_tmp = free_char(token_tmp);
		i += offset;
	}
}
