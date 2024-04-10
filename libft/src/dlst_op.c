/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:37:02 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/02/26 11:28:12 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	insert_front(t_node **head, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->value = value;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_after(t_node *prev_node, int value)
{
	t_node	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->value = value;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_end(t_node **head, int value)
{
	t_node	*new_node;
	t_node	*tmp_node;

	tmp_node = *head;
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->value = value;
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

void	display_list(t_node *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		ft_printf("%d->", node->value);
		node = node->next;
		i++;
	}
	if (node == NULL)
		ft_printf("NULL | stack_size = %d \n", i);
}

int	cmp_value_list(t_node *node, int value)
{
	while (node != NULL)
	{
		if (node->value == value)
			return (1);
		node = node->next;
	}
	if (node == NULL)
		return (0);
	return (0);
}
