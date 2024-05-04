/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:40:58 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 12:42:41 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lt_rules(t_cli *cli, t_token *token)
{
	if (ft_strcmp(token->token, LESS_THAN) == 0)
		if (token->index == get_last_index(cli->token))
			syntax_error(cli, "newline");
}

void	redirect_rules(t_cli *cli, t_token *token)
{
	if (token->next == NULL)
		syntax_error(cli, "newline");
	/*if (token->token[0] == '<')
		lt_rules(cli, token, r_operat, len_operat);
	else if (token->token[0] == '>')
		gt_rules(cli, token, r_operat, len_operat);
	else
		return ;*/
}
