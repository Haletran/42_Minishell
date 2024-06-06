/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:06:46 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/05 16:38:37 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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

int	add_var(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_var_lst;
	if (check_valid_identifier(tmp) == ERROR)
		return (ERROR);
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	env->next->key = ft_strdup(tmp[0]);
	if (!ft_strncmp(tmp[1], "$", 1))
	{
		env->next->value = expand_var(mnsh, ft_strdup(tmp[1]));
		env->next->next = NULL;
		free_tab(tmp);
		return (SUCCESS);
	}
	env->next->value = ft_strdup(tmp[1]);
	env->next->next = NULL;
	free_tab(tmp);
	return (SUCCESS);
}

int	add_back(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	*value;
	char	*to_keep;
	char	**tmp;

	tmp = ft_split(str[i], '+');
	to_keep = ft_strtrim(tmp[1], "=");
	env = mnsh->env_var_lst;
	if (check_valid_identifier(tmp) == ERROR)
		return (ERROR);
	if (not_existing(mnsh, tmp) == ERROR)
		return (ERROR);
	while (env)
	{
		if (!ft_strcmp(env->key, tmp[0]))
		{
			if (!env->value)
			{
				env->value = ft_strdup(to_keep);
				break ;
			}
			value = ft_strdup(env->value);
			env->value = free_char(env->value);
			env->value = ft_strjoin(value, to_keep);
			env->print = 0;
			value = free_char(value);
			break ;
		}
		env = env->next;
	}
	free_tab(tmp);
	to_keep = free_char(to_keep);
	return (SUCCESS);
}