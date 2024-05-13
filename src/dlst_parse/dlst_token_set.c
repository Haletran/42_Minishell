/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_token_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/11 14:45:24 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	delete_node_token(t_token **head, t_token *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node->token);
	del_node->token = NULL;
	free(del_node);
	del_node = NULL;
}

void	delete_all_nodes_token(t_token **head)
{
	t_token	*tmp;

	if (*head == NULL)
	{
		display_error("head is null, deletion is not possible", NULL,
			DEBUG_MODE);
		return ;
	}
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_token(head, *head);
		*head = tmp;
	}
}

void	insert_token_front(t_token **head, char *token, t_token_type type,
		int index)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->token = token;
	new_node->type = type;
	new_node->index = index;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_token_after(t_token *prev_node, char *token, t_token_type type,
		int index)
{
	t_token	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->token = token;
	new_node->type = type;
	new_node->index = index;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_token_end(t_token **head, char *token, t_token_type type,
		int index)
{
	t_token	*new_node;
	t_token	*tmp_node;

	tmp_node = *head;
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->token = token;
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
