/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varloc_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:28:10 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/05 14:09:45 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	varloc_creation(t_cli *cli)
{
	t_bool	ret;
	t_token	*tmp;
	char	*var_line;
	char	*key_line;

	ret = STOPPED;
	tmp = cli->token;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->token, '=') && tmp->type == COMMAND)
		{
			key_line = key_from_token(tmp->token);
			var_line = variable_from_token(tmp->token);
			if (!var_line)
				return (STOPPED);
			ret = varloc_modify(cli, key_line, var_line);
			free(key_line);
			free(var_line);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	varloc_modify(t_cli *cli, char *key_line, char *var_line)
{
	t_variable	*tmp;
	int			i;
	static int	index = 0;

	tmp = cli->variable;
	if (tmp == NULL)
		return (varloc_attrib(cli, key_line, var_line, index++));
	while (ft_strcmp(tmp->key, key_line) != 0 || tmp != NULL)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->key, key_line) == 0)
	{
		i = tmp->index;
		varloc_attrib(cli, key_line, var_line, i);
		delete_node_variable(&cli->variable, tmp);
		return (SUCCESS);
	}
	else
		return (varloc_attrib(cli, key_line, var_line, index++));
	return (STOPPED);
}

int	varloc_attrib(t_cli *cli, char *key_line, char *var_line, int index)
{
	insert_variable_end(&cli->variable, ft_strdup(key_line),
		ft_strdup(var_line), index);
	if (cli->variable == NULL)
		return (STOPPED);
	return (SUCCESS);
}

char	*key_from_token(char *token)
{
	char	*key;
	int		i;

	i = 0;
	while (token[i] != '=')
		i++;
	key = ft_substr(token, 0, i);
	return (key);
}

char	*variable_from_token(char *token)
{
	char	*variable;
	int		i;
	int		j;

	i = 0;
	while (token[i] != '=')
		i++;
	j = ft_strlen_endc(token + i + 1, 0);
	variable = ft_substr(token, i + 1, j);
	return (variable);
}
