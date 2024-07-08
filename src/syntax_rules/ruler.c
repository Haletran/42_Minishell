/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:01:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/08 13:37:07 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*prev_selector(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->prev == NULL)
		return (tmp);
	tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == SPACE_HOLDER)
			tmp = tmp->prev;
		else
		{
			return (tmp);
		}
	}
	return (tmp);
}

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
		else if (ft_isthis(tmp->token, '*') != 0 && tmp->type != 10
			&& tmp->type != 7)
			syntax_error(cli, tmp->token);
		tmp = tmp->next;
	}
}

void	syntax_error(t_cli *cli, char *token)
{
	if (ft_isthis(token, '*') != 0)
	{
		ft_printf_fd(2, SYNTAX_AMB, token);
		cli->mnsh->exit_code = 1;
	}
	else
	{
		ft_printf_fd(2, SYNTAX_UNEXP, token, token);
		cli->mnsh->exit_code = 2;
	}
	cli->rules_flag = 1;
}
