/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:12:03 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 15:35:44 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*freed_key_value(t_env *env)
{
	env->key = free_char(env->key);
	env->value = free_char(env->value);
	return (env->next);
}

void	delete_var(t_lst *mnsh, char *str)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
		{
			env = env->next;
			if (!env)
				break ;
			delete_node_env(&mnsh->env_var_lst, env->prev);
		}
		else
		{
			if (env->next)
				env = env->next;
			else
				break ;
		}
	}
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
