/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:07:51 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/22 15:35:44 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_back(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	*value;
	char	*to_keep;
	char	**tmp;

	tmp = ft_split(str[i], '+');
	to_keep = ft_strtrim(tmp[1], "=");
	env = mnsh->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i])))
		{
			value = ft_strdup(env->value);
			env->value = free_char(env->value);
			env->value = ft_strjoin(value, to_keep);
			value = free_char(value);
			break ;
		}
		env = env->next;
	}
	free_tab(tmp);
	to_keep = free_char(to_keep);
	add_back2(mnsh, str, i);
	return (ERROR);
}

int	check_valid_identifier(char **str)
{
	char **tmp;
	int i;

	i = 0;
	tmp = ft_split(str[1], '=');
	if (!tmp[0])
		return (ERROR);
	while (tmp[0][i])
	{
		if (!ft_isalpha(tmp[0][i]) || tmp[0][i] == '-')
		{
			if (tmp[0][i] == '+')
				i++;
			else
				return (ERROR);
		}
		i++;
	}
	if (tmp[1])
	{
		if (ft_strlen(tmp[1]) == 0)
			return (ERROR);
	}
	return (SUCCESS);
}