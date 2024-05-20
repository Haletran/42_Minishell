/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/20 16:53:44 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replacement(t_token *tmp, char *value, char *key, int str_token_len)
{
	char	*new_token;

	new_token = ft_substr(tmp->token, 0, str_token_len);
	new_token = ft_strjoin_f(new_token, value);
	free_char(tmp->token);
	tmp->token = new_token;
	key = free_char(key);
	value = free_char(value);
}

void	parameter_expansion(t_cli *cli)
{
	t_token	*tmp;
	char	*key;
	char	*value;
	int		i;

	tmp = cli->token;
	while (tmp)
	{
		i = 0;
		while (tmp->token[i] && tmp->token[i] != '$')
			i++;
		key = ft_substr(tmp->token, i + 1, ft_strlen(tmp->token) - (i - 1));
		if (key == NULL)
			return ;
		else if (key[0] == '?')
			value = ft_itoa(cli->mnsh->exit_code);
		else
			value = ft_strdup(get_value_from_key(cli->mnsh->env_cpy_lst, key));
		if (value == NULL)
			value = ft_strdup(get_variable_from_key(cli->variable, key));
		if (value == NULL)
			value = ft_strdup(tmp->token);
		else
			replacement(tmp, value, key, i);
		tmp = tmp->next;
	}
}

// void	parameter_expansion(t_cli *cli)
//{
//	t_token	*tmp;
//	char	*key;
//
//	tmp = cli->token;
//	while (tmp)
//	{
//		if (tmp->token[0] == '$' && tmp->token[1] == '?')
//		{
//			free(tmp->token);
//			tmp->token = ft_itoa(cli->mnsh->exit_code);
//		}
//		else if (tmp->token[0] == '$' && tmp->type != IMMUTABLE)
//		{
//			key = ft_substr(tmp->token, 1, ft_strlen(tmp->token) - 1);
//			free(tmp->token);
//			tmp->token = ft_strdup(get_value_from_key(cli->mnsh->env_cpy_lst,
//						key));
//			if (tmp->token == NULL)
//				tmp->token = ft_strdup(get_variable_from_key(cli->variable,
//							key));
//			if (tmp->token == NULL)
//				tmp->token = ft_strdup("");
//			free(key);
//		}
//		tmp = tmp->next;
//	}
//}
