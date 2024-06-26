/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:01:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/24 15:10:04 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

t_token	*next_selector(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->next == NULL)
		return (tmp);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == SPACE_HOLDER)
			tmp = tmp->next;
		else
		{
			return (tmp);
		}
	}
	return (tmp);
}

void	rulers(t_cli *cli)
{
	t_token	*tmp;

	cli->rules_flag = 0;
	tmp = cli->token;
	while (tmp)
	{
		if ((tmp->type == 2 || tmp->type == 8) && cli->rules_flag == 0)
			redirect_rules(cli, tmp);
		else if (tmp->type == CONTROLE_OPERATOR && cli->rules_flag == 0)
			control_rules(cli, tmp);
		else if (tmp->type == KEYWORD && cli->rules_flag == 0)
			process_error(cli, tmp->token);
		else if (ft_isthis(tmp->token, '*') != 0 && tmp->type != 10 && tmp->type != 7)
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
					"minishell: bash reserved keyword: no \
		implementation required for `%s'\n",
					token);
	cli->mnsh->exit_code = 2;
	cli->rules_flag = 1;
}
