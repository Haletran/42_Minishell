/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:28:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/03 16:07:45 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_arg_redirection(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp != NULL && tmp->type != CONTROLE_OPERATOR)
	{
		if (tmp->type == ARGUMENT && tmp->prev->type == REDIRECTION_OPERATOR)
		{
			if (!ft_strncmp(tmp->prev->token, ">", 1))
				i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	create_redirection_out(t_cli *cli)
{
	t_token	*tmp;
	t_com	*tmp_com;
	int		i;

	tmp_com = get_last_command(cli->com);
	tmp = get_redirection(cli->token, tmp_com->index);
	i = find_arg_redirection(tmp);
	if (i > 0)
	{
		tmp_com->redirection_out = calloc(i + 1, sizeof(char *));
		i = 0;
		while (tmp != NULL && (tmp->type == ARGUMENT
				|| tmp->type == REDIRECTION_OPERATOR))
		{
			if (tmp->type == ARGUMENT
				&& tmp->prev->type == REDIRECTION_OPERATOR)
				tmp_com->redirection_out[i++] = ft_strdup(tmp->token);
			tmp = tmp->next;
		}
		tmp_com->redirection_out[i] = NULL;
	}
}
