/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_redirection_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/22 10:49:29 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_redirection_file_from_index(t_redirection *head, int index)
{
	if (!head)
		return (NULL);
	while (head)
	{
		if (head->index == index)
			return (head->file);
		head = head->next;
	}
	return (NULL);
}

int	get_last_index_redi(t_redirection *head)
{
	if (!head)
		return (-1);
	while (head->next)
		head = head->next;
	return (head->index);
}

void	print_dlst_redirection(t_redirection *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("NODE %d -> type: %d, file: %s, index: %d\n", i, head->type,
			head->file, head->index);
		head = head->next;
		i++;
	}
}
