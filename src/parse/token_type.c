/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:12:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/20 01:36:17 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	ft_lencmparray(char *token, char **array)
{
	int	i;
	int	tmp;

	i = 0;
	while (array[i])
	{
		tmp = ft_strlen(array[i]);
		if (ft_strncmp(token, array[i++], tmp) == 0)
			return (tmp);
	}
	return (0);
}

int	ft_lenstrtype(char *token, t_cli *cli)
{
	int	i;

	i = 0;
	i += ft_lencmparray(token, cli->redirect);
	i += ft_lencmparray(token, cli->control);
	i += ft_lencmparray(token, cli->bracket);
	i += ft_lencmparray(token, cli->keyword);
	i += ft_lencmparray(token, cli->spe_param);
	return (i);
}

t_token_type	token_type_discovery(char *token, t_cli *cli)
{
	if (ft_isthis("\"'<", token[0]) > 0 || cli->flag_quote & 1
		|| cli->flag_dquote & 1)
	{
		return (quote_n_heredoc_census(token, cli));
	}
	if (cli->heredoc == 1 && ft_isthis(" \t\n", token[0]) == 0)
		return (quote_n_heredoc_census(token, cli));
	if (ft_lencmparray(token, cli->redirect) > 0)
		return (REDIRECTION_OPERATOR);
	if (ft_lencmparray(token, cli->control) > 0)
		return (CONTROLE_OPERATOR);
	if (ft_lencmparray(token, cli->bracket) > 0)
		return (BRACKET);
	if (cli->token == NULL || ft_iscontrol(get_token_from_index(cli->token,
				get_last_index(cli->token)), cli) > 0)
		return (COMMAND);
	return (ARGUMENT);
}

t_token_type	token_type_rediscovery(t_token *tok, t_cli *cli)
{
	if (cli->heredoc == 1 && ft_isthis(" \t\n<", tok->token[0]) == 0)
		return (quote_n_heredoc_census(tok->token, cli));
	else if (cli->flag_dquote & 1)
		return (FREEZE);
	else if (cli->flag_quote & 1)
		return (IMMUTABLE);
	if (tok->type == HEREDOC)
		return (HEREDOC);
	if (ft_lencmparray(tok->token, cli->redirect) > 0)
		return (REDIRECTION_OPERATOR);
	if (ft_lencmparray(tok->token, cli->control) > 0)
		return (CONTROLE_OPERATOR);
	if (ft_lencmparray(tok->token, cli->bracket) > 0)
		return (BRACKET);
	if (tok->prev != NULL)
		if (tok->prev->type == REDIRECTION_OPERATOR)
			return (REDIRECTION_ARGUMENT);
	if (command_census(tok, cli) == COMMAND)
		return (COMMAND);
	return (ARGUMENT);
}
