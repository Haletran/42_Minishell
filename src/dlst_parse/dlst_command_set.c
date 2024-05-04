/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_command_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/04 16:20:52 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_com(t_com **head, t_com *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	del_node->command = free_char(del_node->command);
	del_node->env_path = free_char(del_node->env_path);
	if (del_node->arg != NULL)
		delete_all_nodes_arg(&del_node->arg);
	del_node->redirection = free_char(del_node->redirection);
	free(del_node);
}

void	delete_all_nodes_com(t_com **head)
{
	t_com	*tmp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_com(head, *head);
		*head = tmp;
	}
}

void	insert_com_front(t_com **head, char *command, int index)
{
	t_com	*new_node;

	new_node = (t_com *)malloc(sizeof(t_com));
	new_node->command = command;
	new_node->index = index;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_com_after(t_com *prev_node, char *command, int index)
{
	t_com	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_com *)malloc(sizeof(t_com));
	new_node->command = command;
	new_node->index = index;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_com_end(t_com **head, char *command, int index)
{
	t_com	*new_node;
	t_com	*tmp_node;

	tmp_node = *head;
	new_node = (t_com *)malloc(sizeof(t_com));
	new_node->command = command;
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
