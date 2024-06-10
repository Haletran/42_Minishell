/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:28:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/10 20:36:04 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redi_type	redirection_census(char *token)
{
/* 	if (!token)
		return (-1); */
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
    t_redirection	*red;
    t_redi_type		type;
    t_com		*com;
    
    if (!cli || !cli->token || !cli->com) return;
    
    tmp = cli->token;
    com = cli->com;
    while (tmp)
    {
        if (tmp->type == REDIRECTION_OPERATOR)
        {
            type = redirection_census(tmp->token);
            if (type >= 0)
            {
                red = ft_calloc(1, sizeof(t_redirection));
                if (!red) return; // Check if memory allocation was successful
                red->type = type;
                tmp = tmp->next;
                if (tmp && tmp->token)
                {
                    red->file = ft_strdup(tmp->token);
                    if (!red->file) return; // Check if memory allocation was successful
                    red->next = com->redirection;
                    com->redirection = red;
                }
            }
        }
        else if (tmp->type == CONTROLE_OPERATOR)
        {
            com = com->next;
            if (!com) return; // Check if the next command exists
        }
        tmp = tmp->next;
    }
}
