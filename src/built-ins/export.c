/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/27 23:33:34 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var(t_lst *mnsh, char *str)
{
	t_env	*env;
	char	**tmp;

	env = mnsh->env_var_lst;
	if (!str)
		return (NULL);
	tmp = ft_split(str, '$');
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

int	replace_var(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	env = mnsh->env_var_lst;
	if (check_valid_identifier(str[i]) == ERROR)
		return (ERROR);
	tmp = ft_split(str[i], '=');
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i]))
			&& ft_strlen(env->key) == ft_strlen(tmp[0]))
		{
			free(env->value);
			chk_tmp(env, tmp);
			free_tab(tmp);
			return (SUCCESS);
		}
		env = env->next;
	}
	free_tab(tmp);
	return (SUCCESS);
}

int	ft_export(t_lst *mnsh, char **str)
{
	int	i;
	int	err;

	i = 0;
	if (!str[1])
	{
		if (!mnsh->env_var_lst)
			return (ERROR);
		cpy_process(mnsh);
		return (SUCCESS);
	}
	while (str[++i])
	{
		add_process(mnsh, str, i, &err);
		if (err == ERROR)
		{
			ft_printf_fd(2, EXPORT_NOT_VALID, str[i]);
			return (ret_code(mnsh, 1));
		}
	}
	return (ret_code(mnsh, 0));
}
