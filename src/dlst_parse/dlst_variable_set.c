/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_variable_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:25:43 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:26:26 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_variable(t_variable **head, t_variable *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node->key);
	free(del_node->variable);
	free(del_node);
}

void	delete_all_nodes_variable(t_variable **head)
{
	t_variable	*tmp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_variable(head, *head);
		*head = tmp;
	}
}

void	insert_variable_front(t_variable **head, char *key, char *variable,
		int index)
{
	t_variable	*new_node;

	new_node = (t_variable *)malloc(sizeof(t_variable));
	new_node->variable = variable;
	new_node->key = key;
	new_node->index = index;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_variable_after(t_variable *prev_node, char *key, char *variable,
		int index)
{
	t_variable	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_variable *)malloc(sizeof(t_variable));
	new_node->variable = variable;
	new_node->key = key;
	new_node->index = index;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_variable_end(t_variable **head, char *key, char *variable,
		int index)
{
	t_variable	*new_node;
	t_variable	*tmp_node;

	tmp_node = *head;
	new_node = (t_variable *)malloc(sizeof(t_variable));
	new_node->variable = variable;
	new_node->key = key;
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
