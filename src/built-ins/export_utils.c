/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:24:41 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/01 09:00:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	chk_tmp(t_env *env, char **tmp)
{
	if (!tmp[1])
	{
		env->value = NULL;
		env->print = 1;
	}
	else
	{
		env->value = ft_strdup(tmp[1]);
		env->print = 0;
	}
}

t_env	*cpy_env_var(t_env *cpy)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*head;

	new = ft_calloc(1, sizeof(t_env));
	head = new;
	tmp = cpy;
	while (tmp)
	{
		new->key = ft_strdup(tmp->key);
		new->value = ft_strdup(tmp->value);
		new->print = tmp->print;
		if (tmp->next)
		{
			new->next = ft_calloc(1, sizeof(t_env));
			new = new->next;
		}
		tmp = tmp->next;
	}
	return (head);
}

void	add_process(t_lst *mnsh, char **str, int i, int *err)
{
	if (ft_strchr(str[i], '+'))
		(*err) = add_back(mnsh, str, i);
	else if (ft_strchr(str[i], '=') && !already_exist(mnsh, str, i))
		(*err) = add_var(mnsh, str, i);
	else if (!ft_strchr(str[i], '=') && !already_exist(mnsh, str, i))
		(*err) = add_var_no_input(mnsh, str, i);
	else
		(*err) = replace_var(mnsh, str, i);
}

void	cpy_process(t_lst *mnsh)
{
	t_env	*cpy;

	cpy = cpy_env_var(mnsh->env_var_lst);
	sort_in_ascii(cpy);
	print_list_export(cpy);
	mnsh->exit_code = 0;
	delete_all_nodes_env(&cpy);
}
