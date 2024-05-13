/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:01:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 15:20:28 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
			control_rules(cli, tmp);
		else if (tmp->type == KEYWORD)
			process_error(cli, tmp->token);
		tmp = tmp->next;
	}
}

void	syntax_error(t_cli *cli, char *token)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	cli->mnsh->exit_code = 2;
}

void	process_error(t_cli *cli, char *token)
{
	ft_printf_fd(2,
		"minishell: bash reserved keyword: no implementation required for `%s'\n",
		token);
	cli->mnsh->exit_code = 2;
}