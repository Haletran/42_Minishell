/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/20 11:13:37 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	parameter_expansion(t_cli *cli)
{
	t_token	*tmp;
	char	*key;

	tmp = cli->token;
	while (tmp)
	{
		if (tmp->token[0] == '$')
		{
			key = ft_substr(tmp->token, 1, ft_strlen(tmp->token) - 1);
			free(tmp->token);
			tmp->token = get_value_from_key(cli->args->env_cpy_lst, key);
			if (tmp->token == NULL)
				tmp->token = get_variable_from_key(cli->variable, key);
			if (tmp->token == NULL)
				tmp->token = ft_strdup("");
			free(key);
		}
		tmp = tmp->next;
	}
}
