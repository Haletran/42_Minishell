/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/25 13:20:14 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **str)
{
	int	i;
	int	size;

	if (str == NULL)
		return ;
	i = 0;
	size = get_nbargs(str);
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	//free(str);
}

/* void	free_list(t_lst **lst)
{
	free(*lst);
} */



