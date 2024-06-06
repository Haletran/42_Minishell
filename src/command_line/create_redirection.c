/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:28:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/05 16:31:14 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

t_redi_type	redirection_census(char *token)
{
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
	while (tmp != NULL && tmp->type != CONTROLE_OPERATOR)
	{
		type = redirection_census(tmp->token);
		tmp = tmp->next;
		insert_redirection_end(&tmp_com->redirection, ft_strdup(tmp->token),
			type, i++);
		tmp = tmp->next;
	}
}
