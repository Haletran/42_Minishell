/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:28:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/07 12:03:28 by bapasqui         ###   ########.fr       */
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

void	create_redirection(t_cli *cli)
{
	t_token		*tmp;
	t_com		*tmp_com;
	int			i;
	t_redi_type	type;

	tmp_com = get_last_command(cli->com);
	tmp = get_redirection(cli->token, tmp_com->index);
	i = 0;
	while (tmp != NULL && tmp->type != CONTROLE_OPERATOR && tmp->type != COMMAND)
	{
		type = redirection_census(tmp->token);
		tmp = tmp->next;
		insert_redirection_end(&tmp_com->redirection, ft_strdup(tmp->token),
			type, i++);
		tmp = tmp->next;
	}
}
