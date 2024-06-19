/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_command_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/19 08:57:37 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_redi(t_redirection **head, t_redirection *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	if (del_node->file != NULL)
		free(del_node->file);
	free(del_node);
}

void	delete_all_nodes_redi(t_redirection **head)
{
	t_redirection	*tmp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		delete_node_redi(head, *head);
		*head = tmp;
	}
}

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
	if (del_node->command != NULL)
		free_tab(del_node->command);
	if (del_node->redirection != NULL)
		delete_all_nodes_redi(&del_node->redirection);
	if (del_node->env_path != NULL)
		del_node->env_path = free_char(del_node->env_path);
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
