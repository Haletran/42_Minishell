/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alphanode_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:37:02 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/02/27 20:20:49 by aska             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	insert_front_alpha(t_alphanode **head, char **letter)
{
	t_alphanode	*new_node;

	new_node = (t_alphanode *)malloc(sizeof(t_alphanode));
	new_node->letter = letter;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_after_alpha(t_alphanode *prev_node, char **letter)
{
	t_alphanode	*new_node;

	if (prev_node == NULL)
		display_error("Previous node cannot be null", NULL, DEBUG_MODE);
	new_node = (t_alphanode *)malloc(sizeof(t_alphanode));
	new_node->letter = letter;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void	insert_end_alpha(t_alphanode **head, char **letter)
{
	t_alphanode	*new_node;
	t_alphanode	*tmp_node;

	tmp_node = *head;
	new_node = (t_alphanode *)malloc(sizeof(t_alphanode));
	new_node->letter = letter;
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

void	display_alpha(t_alphanode *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		ft_printf("%d->", node->letter);
		node = node->next;
		i++;
	}
	if (node == NULL)
		ft_printf("NULL | stack_size = %d \n", i);
}

int	cmp_letter_list(t_alphanode *node, char **letter)
{
	while (node != NULL)
	{
		if (node->letter == letter)
			return (1);
		node = node->next;
	}
	if (node == NULL)
		return (0);
	return (0);
}
