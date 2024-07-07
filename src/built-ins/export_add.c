/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:06:46 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/07 16:59:46 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_var_no_input(t_lst *mnsh, char **str, int i)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	if (check_identifier(str[i], 0) == ERROR || check_var_found(env, str[i]))
		return (ERROR);
	insert_env_end(&env, ft_strdup(str[i]), NULL);
	if ((!env) || (!env->key))
		return (ERROR);
	return (SUCCESS);
}

int	add_var(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = mnsh->env_var_lst;
	if (check_identifier(str[i], 0) == ERROR)
		return (ERROR);
	key = ft_substr(str[i], 0, ft_strlen_endc(str[i], '='));
	if (!key)
		return (ERROR);
	value = ft_strdup(ft_strchr(str[i++], '=') + 1);
	if (!value)
		return (free_char(key), ERROR);
	insert_env_end(&env, ft_strdup(key), ft_strdup(value));
	key = free_char(key);
	value = free_char(value);
	while (env->next != NULL)
		env = env->next;
	if ((!env) || (!env->key) || (!env->value))
		return (ERROR);
	return (SUCCESS);
}

void	env_dup(t_env *env, char *value, char *to_keep, char **tmp)
{
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
}

int	add_back(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	*value;
	char	*to_keep;
	char	**tmp;

	value = NULL;
	env = mnsh->env_var_lst;
	if (check_identifier(str[i], 1) == ERROR)
		return (ERROR);
	tmp = ft_split(str[i], '+');
	to_keep = ft_strtrim(tmp[1], "=");
	if (not_existing(mnsh, tmp) == ERROR)
	{
		free_tab(tmp);
		to_keep = free_char(to_keep);
		return (ERROR);
	}
	env_dup(env, value, to_keep, tmp);
	free_tab(tmp);
	to_keep = free_char(to_keep);
	return (SUCCESS);
}
