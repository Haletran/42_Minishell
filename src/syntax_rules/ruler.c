/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:01:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 12:38:18 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rulers(t_cli *cli)
{
	t_token	*tmp;

	tmp = cli->token;
	while (tmp)
	{
		if (tmp->type == REDIRECTION_OPERATOR)
			redirect_rules(cli, tmp);
		else if (tmp->type == CONTROLE_OPERATOR)
		{
			ft_printf(BWHT "CONTROLE WAY\n");
			ft_printf(BWHT "type=%d\n" CRESET, tmp->type);
			control_rules(cli, tmp);
		}
		else if (tmp->type == KEYWORD)
		{
			ft_printf(BWHT "KEYWORD WAY\n");
			ft_printf(BWHT "type=%d\n" CRESET, tmp->type);
			syntax_error(cli, tmp->token);
		}
		tmp = tmp->next;
	}
}

void	syntax_error(t_cli *cli, char *token)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	cli->mnsh->exit_code = 2;
}
