/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_redir_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:59:08 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 13:35:45 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_redirection(t_redirection **head, t_redirection *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	del_node->file = free_char(del_node->file);
	free(del_node);
}

void	delete_all_nodes_redirection(t_redirection **head)
{
	t_redirection	*tmp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_redirection(head, *head);
		*head = tmp;
	}
}

void	insert_redirection_front(t_redirection **head, char *file,
		t_redi_type type, int index)
{
	t_redirection	*new_node;

	new_node = malloc(sizeof(t_redirection));
	new_node->type = type;
	new_node->file = file;
	new_node->index = index;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_redirection_after(t_redirection *prev_node, char *file,
		t_redi_type type, int index)
{
	t_redirection	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = malloc(sizeof(t_redirection));
	new_node->type = type;
	new_node->file = file;
	new_node->index = index;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_redirection_end(t_redirection **head, char *file,
		t_redi_type type, int index)
{
	t_redirection	*new_node;
	t_redirection	*tmp_node;

	tmp_node = *head;
	new_node = malloc(sizeof(t_redirection));
	new_node->type = type;
	new_node->file = file;
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
