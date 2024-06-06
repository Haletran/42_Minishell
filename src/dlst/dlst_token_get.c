/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_token_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/05 13:11:19 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

char	*get_token_from_index(t_token *head, int index)
{
	if (!head || index < 0)
		return (NULL);
	while (head)
	{
		if (head->index == index)
			return (head->token);
		head = head->next;
	}
	return (NULL);
}

int	get_type_from_token(t_token *head, char *token)
{
	if (!head || !token)
		return (-1);
	while (head)
	{
		if (!ft_strcmp(head->token, token))
			return (head->type);
		head = head->next;
	}
	return (-1);
}

int	get_last_index(t_token *head)
{
	if (!head)
		return (-1);
	while (head->next)
		head = head->next;
	return (head->index);
}

void	print_dlst_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next)
	{
		ft_printf("token: %s\n", tmp->token);
		ft_printf("type: %s\n", tmp->type);
		ft_printf("index: %d\n", tmp->index);
		tmp = tmp->next;
	}
	ft_printf_fd(1, "token: %s\n", tmp->token);
	ft_printf_fd(1, "type: %s\n", tmp->type);
	ft_printf("index: %d\n", tmp->index);
}

t_token	*get_redirection(t_token *head, int start)
{
	t_token *tmp;

	tmp = head;
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == REDIRECTION_OPERATOR)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}