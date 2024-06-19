/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_command_insert.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:56:20 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/19 08:59:27 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_com_front(t_com **head, int type, int index)
{
	t_com	*new_node;

	new_node = (t_com *)malloc(sizeof(t_com));
	new_node->type = type;
	new_node->index = index;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_com_after(t_com *prev_node, int type, int index)
{
	t_com	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_com *)malloc(sizeof(t_com));
	new_node->type = type;
	new_node->index = index;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_com_end(t_com **head, int type, int index)
{
	t_com	*new_node;
	t_com	*tmp_node;

	tmp_node = *head;
	new_node = (t_com *)malloc(sizeof(t_com));
	new_node->type = type;
	new_node->index = index;
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return ;
	}
	while (tmp_node->next != NULL)
		tmp_node = tmp_node->next;
	tmp_node->next = new_node;
	new_node->prev = tmp_node;
}
