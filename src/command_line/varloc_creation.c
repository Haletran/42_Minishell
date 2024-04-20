/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varloc_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:28:10 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/20 11:13:19 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	varloc_creation(t_cli *cli)
{
	t_token		*tmp;
	char		**var_array;
	static int	i = 0;

	tmp = cli->token;
	while (tmp != NULL)
	{
		if (tmp->type == COMMAND && ft_strchr(tmp->token, '='))
		{
			var_array = ft_split(tmp->token, '=');
			if (var_array[0] && var_array[1])
			{
				insert_variable_end(&cli->variable, ft_strdup(var_array[0]),
					ft_strdup(var_array[1]), i++);
			}
			free_tab(var_array);
		}
		tmp = tmp->next;
	}
}
