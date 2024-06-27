/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_chk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:07:51 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/27 23:16:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	not_existing(t_lst *mnsh, char **str)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	if (check_valid_identifier(str[1]) == ERROR)
		return (ERROR);
	if (already_exist(mnsh, str, 0) == 1)
		return (SUCCESS);
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	env->next->key = ft_strdup(str[0]);
	if (!ft_strncmp(str[2], "$", 1))
	{
		env->next->value = expand_var(mnsh, ft_strdup(str[2]));
		env->next->next = NULL;
		return (SUCCESS);
	}
	env->next->value = ft_strdup(str[2]);
	env->next->next = NULL;
	return (SUCCESS);
}

int	already_exist(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i])))
		{
			free_tab(tmp);
			return (1);
		}
		env = env->next;
	}
	free_tab(tmp);
	return (0);
}

int	check_valid_key(char **str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (!ft_strncmp(str[0], "export", ft_strlen(str[0]))
		&& get_nbargs(str) == 2)
		count++;
	while (str[count][++i])
		if (!ft_isalpha(str[count][i]))
			return (ERROR);
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

int	check_valid_identifier(char *str)
{
	char	**tmp;
	int		j;

	j = 0;
	tmp = ft_split(str, '=');
	if (!tmp[0])
		return (free_tab(tmp), ERROR);
	while (tmp[0][j])
	{
		if (!ft_isalpha(tmp[0][j]))
			if (tmp[0][j] != '+' && tmp[0][j] != '_')
				return (free_tab(tmp), ERROR);
		j++;
	}
	j = 0;
	if (!tmp[1])
		return (free_tab(tmp), SUCCESS);
	while (tmp[1][j])
	{
		if (!ft_isprint(tmp[1][j]))
			return (free_tab(tmp), ERROR);
		j++;
	}
	free_tab(tmp);
	return (SUCCESS);
}
