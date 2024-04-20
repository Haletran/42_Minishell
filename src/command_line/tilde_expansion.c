/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/20 12:26:30 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	tilde_expansion(t_cli *cli)
{
	t_token	*tmp;

	tmp = cli->token;
	while (tmp)
	{
		if (tmp->token[0] == '~')
		{
			if (tmp->token[1] == 0)
			{
				free(tmp->token);
				tmp->token = get_value_from_key(cli->args->env_cpy_lst, "HOME");
			}
			else if (tmp->token[1] == '+')
			{
				free(tmp->token);
				tmp->token = get_value_from_key(cli->args->env_cpy_lst, "PWD");
			}
			else if (tmp->token[1] == '-')
			{
				free(tmp->token);
				tmp->token = get_value_from_key(cli->args->env_cpy_lst,
						"OLDPWD");
			}
			if (tmp->token == NULL)
				tmp->token = ft_strdup("\n");
		}
		tmp = tmp->next;
	}
}
