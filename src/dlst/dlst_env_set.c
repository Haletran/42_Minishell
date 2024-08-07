/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_env_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:27:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/07 17:22:42 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_env(t_env **head, t_env *del_node)
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
	del_node->key = NULL;
	free(del_node->value);
	del_node->value = NULL;
	free(del_node);
	del_node = NULL;
}

void	delete_all_nodes_env(t_env **head)
{
	t_env	*tmp;

	if (*head == NULL)
	{
		display_error("head is null, deletion is not possible", NULL,
			DEBUG_MODE);
		return ;
	}
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_env(head, *head);
		*head = tmp;
	}
}

void	insert_env_front(t_env **head, char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = (*head);
	new_node->print = 0;
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_env_after(t_env *prev_node, char *key, char *value)
{
	t_env	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->print = 0;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_env_end(t_env **head, char *key, char *value, int print)
{
	t_env	*new_node;
	t_env	*tmp_node;

	tmp_node = *head;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->value = value;
	new_node->print = print;
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
