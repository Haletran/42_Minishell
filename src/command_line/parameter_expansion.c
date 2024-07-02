/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/02 14:06:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replacement(t_cli *cli, t_p_exp *exp)
{
	char	*new_token;
	char	*r;

	r = NULL;
	exp->value = get_parameter_value(cli, exp->key);
	if (exp->value[0] != 0)
	{
		new_token = ft_substr(exp->tmp->token, 0, exp->d_pos);
		new_token = ft_strjoin_f(new_token, exp->value);
		free_char(exp->tmp->token);
		exp->tmp->token = new_token;
	}
	else if (exp->tmp->type != IMMUTABLE && exp->tmp->type != FREEZE)
	{
		r = ft_substr(exp->tmp->token, 0, ft_strlen_endc(exp->tmp->token, '$'));
		exp->tmp->token = free_char(exp->tmp->token);
		exp->tmp->token = ft_strdup(r);
		r = free_char(r);
	}
	exp->d_count--;
	exp->key = free_char(exp->key);
	exp->value = free_char(exp->value);
}

void	parameter_expansion(t_cli *cli)
{
	t_p_exp	exp;

	init_exp(&exp, cli->token, cli);
	while (exp.tmp)
	{
		exp.d_count = -1;
		while (exp.tmp && exp.d_count != 0)
		{
			exp.d_count = dollar_count(exp.tmp->token);
			exp.d_pos = parse_var_tok(exp.tmp->token, exp.tmp->next, &exp);
			if (exp.d_pos == -1 || exp.tmp->type == IMMUTABLE)
				break ;
			exp.key = ft_substr(exp.tmp->token, exp.d_pos + 1,
					var_len(exp.tmp->token) - 1);
			if (exp.key == NULL)
				return ;
			replacement(cli, &exp);
		}
		exp.tmp = delete_token_empty(cli, exp.tmp);
		if (exp.tmp == NULL)
			break ;
	}
}
