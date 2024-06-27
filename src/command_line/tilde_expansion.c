/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/27 19:18:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tilde_expansion_process(t_token *tmp, char c, char *env_var)
{
	if (!c || !env_var || !tmp->token)
		return ;
	if (tmp->token[1] == c)
	{
		free(tmp->token);
		tmp->token = ft_strdup(env_var);
	}
}

void	tilde_expansion(t_cli *cli)
{
	t_token	*tmp;

	
	tmp = cli->token;
	while (tmp)
	{
		if (tmp->token[0] == '~' && tmp->type != IMMUTABLE)
		{
			tilde_expansion_process(tmp, 0,
				get_value_from_key(cli->mnsh->env_var_lst, "HOME"));
			tilde_expansion_process(tmp, '+',
				get_value_from_key(cli->mnsh->env_var_lst, "PWD"));
			tilde_expansion_process(tmp, '-',
				get_value_from_key(cli->mnsh->env_var_lst, "OLDPWD"));
			if (tmp->token == NULL)
				tmp->token = ft_strdup("\n");
		}
		tmp = tmp->next;
	}
}
