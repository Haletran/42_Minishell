/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/03 16:54:54 by baptiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_value(char **tmp, int j)
{
	if (!tmp[1])
		return (SUCCESS);
	while (tmp[1][j])
	{
		if (ft_isprint(tmp[1][j]) == FALSE)
			return (ERROR);
		j++;
	}
	return (SUCCESS);
}

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
	if (check_valid_identifier(str[i], 0) == ERROR)
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
	if (!mnsh->env_var_lst)
		return (ERROR);
	if (!str[1])
	{
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
