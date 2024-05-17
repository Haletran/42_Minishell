/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:10:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/17 12:10:17 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_old_path(t_lst *lst)
{
	t_env	*env;

	env = lst->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
			break ;
		env = env->next;
	}
	chdir(env->value);
}

static void	update_path(t_lst *lst, char *old_path)
{
	t_env	*env;
	char	curr_path[1024];

	env = lst->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
		{
			free(env->value);
			env->value = ft_strdup(old_path);
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
		return (ft_strdup(getcwd(NULL, 1024)));
	return (env->value);
}

static int	handle_arguments(char **str, t_lst *lst)
{
	if (get_nbargs(str) > 2)
	{
		ft_printf_fd(2, "cd : too many arguments\n");
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
	old_path = ft_strdup(search_path("PWD", lst));
	if (handle_arguments(str, lst) == ERROR)
		exit(1);
	else if (!str[1] || !ft_strncmp(str[1], "--", -1))
	{
		lst->home_path = get_env("HOME", lst);
		if (!lst->home_path)
		{
			ft_printf_fd(2, "minishell : cd : HOME not set\n");
			old_path = free_char(old_path);
			lst->exit_code = 1;
			return (1);
		}
		chdir(lst->home_path);
	}
	else if (!ft_strncmp(str[1], "-", 1) && ft_strlen(str[1]) == 1)
		cd_old_path(lst);
	else
		valid = chdir(str[1]);
	if (valid)
	{
		perror(str[1]);
		lst->exit_code = 1;
		old_path = free_char(old_path);
		return(1);
	}
	update_path(lst, old_path);
	old_path = free_char(old_path);
	lst->exit_code = 0;
	return (0);
}
