/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:12:03 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/30 17:39:26 by bapasqui         ###   ########.fr       */
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
	t_env	*prev;
	t_env	*temp;

	env = mnsh->env_var_lst;
	prev = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
		{
			temp = freed_key_value(env);
			free(env);
			if (prev)
				prev->next = temp;
			else
				mnsh->env_var_lst = temp;
			env = temp;
		}
		else
		{
			prev = env;
			env = env->next;
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
