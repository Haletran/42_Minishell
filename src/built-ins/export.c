/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/15 12:02:49 by bapasqui         ###   ########.fr       */
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
	t_env	*tmp;
	char	*key;

	tmp = NULL;
	env = mnsh->env_var_lst;
	if (check_identifier(str[i], 0) == ERROR)
		return (ERROR);
	key = ft_substr(str[i], 0, ft_strlen_endc(str[i], '='));
	tmp = get_env_var(env, key);
	key = free_char(key);
	if (tmp == NULL)
		return (ERROR);
	tmp->value = free_char(tmp->value);
	tmp->value = ft_strdup(ft_strchr(str[i], '=') + 1);
	if (tmp->value == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	ft_export(t_lst *mnsh, char **str)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!mnsh->env_var_lst)
		return (ERROR);
	if (!str[1])
	{
		cpy_process(mnsh);
		return (SUCCESS);
	}
	while (str[i])
	{
		add_process(mnsh, str, i, &err);
		if (err == ERROR)
		{
			ft_printf_fd(2, EXPORT_NOT_VALID, str[i]);
			return (ret_code(mnsh, 1));
		}
		i++;
	}
	return (ret_code(mnsh, 0));
}
