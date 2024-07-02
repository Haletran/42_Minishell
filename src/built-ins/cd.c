/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:10:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 15:28:56 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		cd_old_path(t_lst *lst)
{
	t_env	*env;

	env = lst->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
			break ;
		env = env->next;
	}
	if (env && env->value)
		chdir(env->value);
	else
		return (10);
	return (SUCCESS);
}

void	update_path(t_lst *lst, char *old_path)
{
	t_env	*env;
	char	curr_path[1024];

	env = lst->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
		{
			if (env->value)
			{
				free(env->value);
				env->value = ft_strdup(old_path);
			}
		}
		else if (!ft_strncmp(env->key, "PWD", 3))
		{
			getcwd(curr_path, 1024);
			free(env->value);
			env->value = ft_strdup(curr_path);
		}
		env = env->next;
	}
}

char	*search_path(char *str, t_lst *lst)
{
	t_env	*env;

	env = lst->env_var_lst;
	if (!str)
		return (NULL);
	while (env)
	{
		if (!env)
			break ;
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
			break ;
		env = env->next;
	}
	if (!env)
		return (getcwd(NULL, 1024));
	return (ft_strdup(env->value));
}

int	handle_arguments(char **str, t_lst *lst)
{
	if (get_nbargs(str) > 2)
	{
		ft_printf_fd(2, CD_TOO_MANY);
		lst->exit_code = 1;
		return (ERROR);
	}
	return (0);
}

int	ft_cd(char **str, t_lst *lst)
{
	int		valid;
	char	*old_path;

	valid = 0;
	old_path = search_path("PWD", lst);
	if (handle_arguments(str, lst) == ERROR)
	{
		old_path = free_char(old_path);
		return (1);
	}
	else if (!str[1] || !ft_strncmp(str[1], "--", -1))
	{
		lst->home_path = get_env("HOME", lst);
		if (!lst->home_path)
		{
			ft_printf_fd(2, CD_HOME_NOT);
			return (return_process(1, old_path, lst));
		}
		valid = chdir(lst->home_path);
	}
	else if (!ft_strncmp(str[1], "-", 1) && ft_strlen(str[1]) == 1)
		valid = cd_old_path(lst);
	else
		valid = chdir(str[1]);
	return (cd_valid(valid, old_path, lst));
}
