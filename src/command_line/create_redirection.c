/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:28:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/26 15:43:27 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redi_type	redirection_census(char *token)
{
	if (!token)
		return (-1);
	if (ft_strcmp(token, "<") == 0)
		return (IN);
	else if (ft_strcmp(token, ">") == 0)
		return (OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPEND_OUT);
	else if (ft_strcmp(token, ">&") == 0)
		return (AND_OUT);
	return (-1);
}

void	handle_redir(t_token *tmp, t_com *com, int *i)
{
	t_redi_type	type;

	type = redirection_census(tmp->token);
	if (type >= 0)
	{
		tmp = tmp->next;
		if (tmp)
			insert_redirection_end(&com->redirection, ft_strdup(tmp->token),
				type, *i);
	}
	(*i)++;
}

void	redirect_attr(t_com *com, t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (com->type == HEREDOC)
			if (com->next)
				com = com->next;
		if (tmp->type == REDIRECTION_OPERATOR)
			handle_redir(tmp, com, &i);
		else if (tmp->type == CONTROLE_OPERATOR)
		{
			com = com->next;
			i = 0;
			if (!com)
				return ;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	create_redirection(t_cli *cli)
{
	t_token	*tmp;
	t_com	*com;

	if (!cli || !cli->token)
		return ;
	tmp = cli->token;
	if (!cli->com)
		cli->com = ft_calloc(1, sizeof(t_com));
	com = cli->com;
	cli->com->redirection = NULL;
	redirect_attr(com, tmp);
}
