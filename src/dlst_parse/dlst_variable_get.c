/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_variable_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/12 14:12:22 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

char	*get_variable_from_key(t_variable *head, char *key)
{
	if (!head || !key)
		return (NULL);
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head->variable);
		head = head->next;
	}
	return (NULL);
}

char	*get_key_from_variable(t_variable *head, char *variable)
{
	if (!head || !variable)
		return (NULL);
	while (head)
	{
		if (!ft_strcmp(head->variable, variable))
			return (head->key);
		head = head->next;
	}
	return (NULL);
}

int	get_last_index_var(t_variable *head)
{
	if (!head)
		return (-1);
	while (head->next)
		head = head->next;
	return (head->index);
}

void	print_dlst_variable(t_variable *head)
{
	t_variable	*tmp;

	tmp = head;
	while (tmp->next)
	{
		ft_printf("%s=\"%s\"\n", tmp->key, tmp->variable);
		tmp = tmp->next;
	}
	ft_printf("%s=\"%s\"\n", tmp->key, tmp->variable);
}
