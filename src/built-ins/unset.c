/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:12:03 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 19:12:03 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*freed_key_value(t_env *env)
{
	env->key = free_char(env->key);
	env->value = free_char(env->value);
	return (env->next);
}

int	check_if_env_found(t_env *env, char *str)
{
	if (!ft_strncmp(env->key, str, ft_strlen(str))
		&& ft_strlen(env->key) == ft_strlen(str))
		return (1);
	return (0);
}

void	delete_var(t_lst *mnsh, char *str)
{
	t_env	*tmp;

	tmp = mnsh->env_var_lst;
	while (tmp->next != NULL && check_if_env_found(tmp, str) == 0)
		tmp = tmp->next;
	if (check_if_env_found(tmp, str) == 1)
	{
		delete_node_env(&mnsh->env_var_lst, tmp);
		tmp = NULL;
	}
	else
		return ;
}

int	ft_unset(char **str, t_lst **mnsh)
{
	int	i;

	i = 1;
	while (str[i])
	{
		delete_var(*mnsh, str[i]);
		i++;
	}
	(*mnsh)->exit_code = 0;
	return (0);
}

