/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:01:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/11 16:45:52 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int rulers(t_cli *cli)
{
	t_token	*tmp;
    int check;

	tmp = cli->token;
    check = 0;
	while (tmp)
	{
		if (tmp->type == REDIRECTION_OPERATOR)
        {
			redirect_rules(cli, tmp);
            check++;
        }
        else if (tmp->type == CONTROLE_OPERATOR)
		{
        	control_rules(cli, tmp);
            check++;
        }
		else if (tmp->type == KEYWORD)
		{
            syntax_error(cli, tmp->token);
            check++;
        }
		tmp = tmp->next;
	}
    return (check);
}

void syntax_error(t_cli *cli, char *token)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	cli->mnsh->exit_code = 2;
}
