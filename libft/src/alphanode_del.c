/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alphanode_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:37:02 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:13:22 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	delete_alphanode(t_alphanode **head, t_alphanode *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node);
}

void	delete_all_alphanodes(t_alphanode **head)
{
	t_alphanode	*tmp;

	if (*head == NULL)
	{
		display_error("head is null, deletion is not possible", NULL,
			DEBUG_MODE);
		return ;
	}
	while (*head != NULL)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}
