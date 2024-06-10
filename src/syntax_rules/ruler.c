/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:01:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/10 16:40:18 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rulers(t_cli *cli)
{
	t_token	*tmp;

	cli->rules_flag = 0;
	tmp = cli->token;
	while (tmp)
	{
		if ((tmp->type == REDIRECTION_OPERATOR || tmp->type == HEREDOC)
			&& cli->rules_flag == 0)
			redirect_rules(cli, tmp);
		else if (tmp->type == CONTROLE_OPERATOR && cli->rules_flag == 0)
			control_rules(cli, tmp);
		else if (tmp->type == KEYWORD && cli->rules_flag == 0)
			process_error(cli, tmp->token);
		else if (ft_isthis(tmp->token, '*') != 0)
			syntax_error(cli, tmp->token);
		tmp = tmp->next;
	}
}

void	syntax_error(t_cli *cli, char *token)
{
	if (ft_isthis(token, '*') != 0)
	{
		ft_printf_fd(2, "minishell: %s: ambiguous redirect\n", token);
		cli->mnsh->exit_code = 1;
	}
	else
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
			token, token);
		cli->mnsh->exit_code = 2;
	}
	cli->rules_flag = 1;
}

void	process_error(t_cli *cli, char *token)
{
	ft_printf_fd(2,
		"minishell: bash reserved keyword: no implementation required for `%s'\n",
		token);
	cli->mnsh->exit_code = 2;
	cli->rules_flag = 1;
}