/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/24 17:40:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replacement(t_token *tmp, char *value, char *key, int str_token_len)
{
	char	*new_token;
	char	*residual;

	residual = NULL;
	if (str_token_len != -1)
	{
		new_token = ft_substr(tmp->token, 0, str_token_len);
		new_token = ft_strjoin_f(new_token, value);
		free_char(tmp->token);
		tmp->token = new_token;
	}
	else
	{
		residual = ft_substr(tmp->token, 0, ft_strlen_endc(tmp->token, '$'));
		tmp->token = free_char(tmp->token);
		tmp->token = ft_strdup(residual);
		residual = free_char(residual);
	}
	key = free_char(key);
	value = free_char(value);
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

int	variable_len(char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i] && token[i] != '$')
		i++;
	while (token[i + j] != 0)
	{
		if (ft_isthis("'\"\0", token[i + j]) > 0)
			return (j);
		j++;
	}
	return (j);
}

int	dollar_position(char *token)
{
	int	i;

	i = 0;
	while (token[i] != 0 && token[i] != '$')
		i++;
	if (token[i] == 0)
		return (-1);
	return (i);
}

void	parameter_expansion(t_cli *cli)
{
	t_token	*tmp;
	char	*key;
	char	*value;
	int		i;

	tmp = cli->token;
	while (tmp && (cli->flag_quote == 0))
	{
		i = dollar_position(tmp->token);
		if (i == -1 || tmp->type == IMMUTABLE)
		{
			tmp = tmp->next;
			continue ;
		}
		key = ft_substr(tmp->token, i + 1, variable_len(tmp->token) - 1);
		if (key == NULL)
			return ;
		else
			value = get_parameter_value(cli, key);
		if (value[0] != 0)
			replacement(tmp, value, key, i);
		else if (tmp->type != FREEZE && tmp->type != IMMUTABLE)
			replacement(tmp, value, key, -1);
		tmp = tmp->next;
	}
}
