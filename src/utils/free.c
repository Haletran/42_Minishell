/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/01 15:13:41 by bapasqui         ###   ########.fr       */
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
	printf("size = %d\n", size);
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	//(void) free(str);
}

void	free_char_double_pointer(char **ptr)
{
	char	**tmp;

	if (ptr)
	{
		tmp = ptr;
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		//free(ptr);
	}
}

/* void	free_list(t_lst **lst)
{
	free(*lst);
} */
