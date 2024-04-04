/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/04 15:14:40 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_env **lst)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
