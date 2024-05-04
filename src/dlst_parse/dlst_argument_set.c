/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_argument_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 12:26:46 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_arg(t_arg **head, t_arg *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node->arg);
	free(del_node);
}

void	delete_all_nodes_arg(t_arg **head)
{
	t_arg	*tmp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_arg(head, *head);
		*head = tmp;
	}
}

void	insert_arg_front(t_arg **head, char *arg)
{
	t_arg	*new_node;

	new_node = (t_arg *)malloc(sizeof(t_arg));
	new_node->arg = arg;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_arg_after(t_arg *prev_node, char *arg)
{
	t_arg	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_arg *)malloc(sizeof(t_arg));
	new_node->arg = arg;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_arg_end(t_arg **head, char *arg)
{
	t_arg	*new_node;
	t_arg	*tmp_node;

	tmp_node = *head;
	new_node = (t_arg *)malloc(sizeof(t_arg));
	new_node->arg = arg;
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
