/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_env_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/19 08:57:56 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_size(t_env *head)
{
	int	size;

	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

int	find_in_env(char *str, t_cli *cli)
{
	t_cli	*tmp;

	tmp = cli;
	while (tmp->mnsh->env_var_lst)
	{
		if (!ft_strcmp(str, tmp->mnsh->env_var_lst->key))
			return (SUCCESS);
		tmp->mnsh->env_var_lst = tmp->mnsh->env_var_lst->next;
	}
	return (ERROR);
}

char	*get_value_from_key(t_env *head, char *key)
{
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	*get_key_from_value(t_env *head, char *value)
{
	while (head)
	{
		if (!ft_strcmp(head->value, value))
			return (head->key);
		head = head->next;
	}
	return (NULL);
}

void	print_dlst(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp->next)
	{
		ft_printf("key: %s\n", tmp->key);
		ft_printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
	ft_printf_fd(1, "key: %s\n", tmp->key);
	ft_printf_fd(1, "value: %s\n", tmp->value);
}
