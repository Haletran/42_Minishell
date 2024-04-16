/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:12:03 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/16 08:09:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_var_cpy(t_lst *args, char *str)
{
	t_env	*env;
	t_env	*prev;
	t_env	*temp;

	env = args->env_cpy_lst;
	prev = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
		{
			free_char(env->key);
			free_char(env->value);
			temp = env->next;
			free(env);
			if (prev)
				prev->next = temp;
			else
				args->env_var_lst = temp;
			env = temp;
		}
		else
		{
			prev = env;
			env = env->next;
		}
	}
}


void	delete_var(t_lst *args, char *str)
{
	t_env	*env;
	t_env	*prev;
	t_env	*temp;

	env = args->env_var_lst;
	prev = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
		{
			free_char(env->key);
			free_char(env->value);
			temp = env->next;
			free(env);
			if (prev)
				prev->next = temp;
			else
				args->env_var_lst = temp;
			env = temp;
		}
		else
		{
			prev = env;
			env = env->next;
		}
	}
}



int	ft_unset(char **str, t_lst **args)
{
	int	i;

	i = 1;
	while (str[i])
	{
		delete_var(*args, str[i]);
		delete_var_cpy(*args, str[i]);
		i++;
	}
	return (SUCCESS);
}
