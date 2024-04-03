/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/03 12:41:22 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void replace_var(t_lst *args, char **str)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[1], '=');
	env = *args->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[1]))
			&& ft_strlen(env->key) == ft_strlen(tmp[0]))
		{
			free(env->value);
			env->value = ft_strdup(tmp[1]);
			free_tab(tmp);
			return ;
		}
		env = env->next;
	}
	free_tab(tmp);
}

void replace_var_cpy(t_lst *args, char **str)
{
	t_env *env;
	char **tmp;
	
	tmp = ft_split(str[1], '=');
	env = *args->env_cpy_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[1]))
			&& ft_strlen(env->key) == ft_strlen(tmp[0]))
		{
			free(env->value);
			env->value = ft_strdup(tmp[1]);
			free_tab(tmp);
			return ;
		}
		env = env->next;
	}
	free_tab(tmp);
}


void	add_var_no_input(t_lst *args, char **str)
{
	t_env	*env;

	env = *args->env_cpy_lst;
	while (env->next)
		env = env->next;
	env->next = malloc(sizeof(t_env));
	env->next->key = ft_strdup(str[1]);
	env->next->value = NULL;
	env->next->next = NULL;
	return ;
}

void	add_var(t_lst *args, char **str)
{
	t_env	*env;
	char **tmp;

	tmp = ft_split(str[1], '=');
	env = *args->env_var_lst;
	while (env->next)
		env = env->next;
	env->next = malloc(sizeof(t_env));
	env->next->key = ft_strdup(tmp[0]);
	env->next->value = ft_strdup(tmp[1]);
	env->next->next = NULL;
	free_tab(tmp);
	return ;
}

int	already_exist(t_lst *args, char **str)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[1], '=');
	env = *args->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[1])))
		{
			free_tab(tmp);
			return (1);
		}
		env = env->next;
	}
	free_tab(tmp);
	return (0);
}

int	ft_export(t_lst *args, char **str)
{
	if (!str[1])
	{
		if (!args->env_cpy_lst)
			return (ERROR);
		sort_in_ascii(*args->env_cpy_lst);
		print_list_export(args);
		return (1);
	}
	if (check_if_alpha(str[1]) == ERROR)
	{
		ft_printf_fd(2, "minishell : %s not a valid identifier\n", str[1]);
		g_value = 1;
		return (ERROR);
	}
	if (ft_strchr(str[1], '=') && !already_exist(args, str))
		add_var(args, str);
	else if (!ft_strchr(str[1], '=') && !already_exist(args, str))
		add_var_no_input(args, str);
	else
	{
		replace_var(args, str);
		replace_var_cpy(args, str);
	}
	return (SUCCESS);
}
