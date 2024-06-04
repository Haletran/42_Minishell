/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/04 23:13:59 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int add_var(t_lst *mnsh, char **str, int i)
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

int	ft_export(t_lst *mnsh, char **str)
{
	int	i;
	int err;

	i = 1;
	if (!str[1])
	{
		if (!mnsh->env_var_lst)
			return (ERROR);
		sort_in_ascii(mnsh->env_var_lst);
		print_list_export(mnsh);
		mnsh->exit_code = 0;
		return (SUCCESS);
	}
	while (str[i])
	{
		if (ft_strchr(str[i], '+'))
			err = add_back(mnsh, str, i);
		else if (ft_strchr(str[i], '=') && !already_exist(mnsh, str, i))
			err = add_var(mnsh, str, i);
		else if (!ft_strchr(str[i], '=') && !already_exist(mnsh, str, i))
			err = add_var_no_input(mnsh, str, i);
		else
			err = replace_var(mnsh, str, i);
		if (err == ERROR)
			break;
		i++;
	}
	if (err == ERROR)
	{
		ft_printf_fd(2, "minishell: export: '%s': not a valid identifier\n",
				str[i]);
		mnsh->exit_code = 1;
		return (mnsh->exit_code);
	}
	mnsh->exit_code = 0;
	return (mnsh->exit_code);
}

