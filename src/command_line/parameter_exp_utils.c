/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_exp_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:29:52 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/26 13:31:40 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	dollar_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != 0)
	{
		if (token[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	init_exp(t_p_exp *exp, t_token *tmp, t_cli *cli)
{
	exp->cli = cli;
	exp->key = NULL;
	exp->value = NULL;
	exp->tmp = tmp;
	exp->var_flag = 0;
	exp->d_pos = 0;
	exp->d_count = -1;
}

char	*get_parameter_value(t_cli *cli, char *key)
{
	char	*value;
	pid_t	pid;

	pid = getpid();
	if (key[0] == '?')
		return (ft_itoa(cli->mnsh->exit_code));
	else if (key[0] == '$')
		return (ft_itoa(pid));
	else
		value = ft_strdup(get_value_from_key(cli->mnsh->env_var_lst, key));
	if (key[0] > 0 && value == NULL)
		value = ft_strdup("");
	else if (value == NULL)
		value = ft_strdup("");
	return (value);
}

int	var_len(char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i] && token[i] != '$')
		i++;
	if (ft_isthis("@#!0-*?$", token[i + 1]) != 0)
		return (2);
	while (token[i + j++] != 0)
		if (ft_isalnum(token[i + j]) == 0 && token[i + j] != '_')
			break ;
	return (j);
}

int	parse_var_tok(char *token, t_token *next_token, t_p_exp *exp)
{
	int i;

	i = 0;
	while (token[i] != 0 && token[i] != '$')
		i++;
	if (token[i] != '$')
		return (-1);
	if (token[i + 1] != 0)
	{
		exp->var_flag = 1;
		return (i);
	}
	if (next_token != NULL)
	{
		if (next_token->type == DQUOTE || next_token->type == QUOTE)
			return (i);
		else
			return (-1);
	}
	else if (next_token == NULL)
		return (-1);
	return (i);
}