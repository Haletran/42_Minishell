/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:28:26 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/24 09:48:37 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	print_list_env(char *string, t_lst *mnsh)
{
	t_env	*current;

	current = mnsh->env_var_lst;
	while (current)
	{
		ft_printf_fd(1, "%s%s%s\n", current->key, string, current->value);
		current = current->next;
	}
}

void	print_list_export(t_lst *mnsh)
{
	t_env	*current;

	current = mnsh->env_cpy_lst;
	while (current)
	{
		if (current->value)
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", current->key,
				current->value);
		else
			ft_printf_fd(1, "declare -x %s\n", current->key);
		current = current->next;
	}
}

void	*ft_lst_new_2(char *index)
{
	t_env	*new;
	char	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split(index, '=');
	new->key = ft_strdup(tmp[0]);
	new->value = ft_strdup(tmp[1]);
	new->next = NULL;
	free_tab(tmp);
	return (new);
}

void	*ft_lstadd_back_2(t_env *lst, char *value)
{
	t_env *head;

	head = lst;
	if (lst == NULL)
	{
		lst = ft_lst_new_2(value);
		return (lst);
	}
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = ft_lst_new_2(value);
	lst = head;
	return (lst);
}