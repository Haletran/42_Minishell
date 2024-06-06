/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/05 13:50:10 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	replace_var(t_lst *mnsh, char **str, int i)
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

int	ft_export(t_lst *mnsh, char **str)
{
	int	i;
	int	err;

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
			break ;
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
