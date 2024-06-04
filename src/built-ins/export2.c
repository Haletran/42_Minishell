/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:06:46 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/04 22:33:10 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var(t_lst *mnsh, char *str)
{
	t_env	*env;
	char	**tmp;

	env = mnsh->env_var_lst;
	tmp = ft_calloc(2, sizeof(char *));
	tmp = ft_split(str, '$');
	if (!str)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(tmp[0]))
			&& ft_strlen(env->key) == ft_strlen(tmp[0]))
		{
			free_tab(tmp);
			return (env->value);
		}
		else
			env = env->next;
	}
	free_tab(tmp);
	return (NULL);
}

int replace_var(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_var_lst;
	if (check_valid_identifier(tmp) == ERROR)
		return (ERROR);
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i]))
			&& ft_strlen(env->key) == ft_strlen(tmp[0]))
		{
			free(env->value);
			env->value = ft_strdup(tmp[1]);
			env->print = 0;
			free_tab(tmp);
			return (SUCCESS);
		}
		env = env->next;
	}
	free_tab(tmp);
	return (SUCCESS);
}


int	check_if_var_exist(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
			return (ERROR);
		env = env->next;
	}
	return (SUCCESS);
}

int	add_var_no_input(t_lst *mnsh, char **str, int i)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	if (check_valid_identifier(str) == ERROR)
		return (ERROR);
	if (check_if_var_exist(env, str[i]))
		return (ERROR);
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	env->next->key = ft_strdup(str[i]);
	env->next->value = NULL;
	env->next->print = 1;
	env->next->next = NULL;
	return (SUCCESS);
}
