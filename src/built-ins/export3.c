/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:07:51 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/04 23:09:46 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	not_existing(t_lst *mnsh, char **str)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	if (check_valid_identifier(str) == ERROR)
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

int check_valid_key(char **str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!ft_strncmp(str[0], "export", ft_strlen(str[0])) && get_nbargs(str) == 2)
		count++;
	while (str[count][++i])
		if (!ft_isalpha(str[count][i]))
			return (ERROR);
	return (SUCCESS);
}

int	check_valid_identifier(char **str)
{
    char	**tmp;
    int		i;
    int		j;

    i = 0;
    if (!str[0])
        return (ERROR);
    while (str[i])
    {
        tmp = ft_split(str[i], '=');
        if (!tmp[0])
            return (free_tab(tmp), ERROR);
        j = 0;
        while (tmp[0][++j])
            if (!ft_isalnum(tmp[0][j]) || tmp[0][j] == '-')
                if (tmp[0][j] != '+')
                    return (free_tab(tmp), ERROR);
        if (tmp[1] && ft_strlen(tmp[1]) == 0)
            return (free_tab(tmp), ERROR);
        free_tab(tmp);
        i++;
    }
    if (check_valid_key(str) == ERROR)
        return (ERROR);
    return (SUCCESS);
}
