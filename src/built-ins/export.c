/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/17 16:12:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (!tmp[1])
			{
				env->print = 1;
				env->value = NULL;
			}
			else
			{
				env->value = ft_strdup(tmp[1]);
				env->print = 0;
			}
			free_tab(tmp);
			return (SUCCESS);
		}
		env = env->next;
	}
	free_tab(tmp);
	return (SUCCESS);
}

t_env	*cpy_env_var(t_env *cpy)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*head;

	new = ft_calloc(1, sizeof(t_env));
	head = new;
	tmp = cpy;
	while (tmp)
	{
		new->key = ft_strdup(tmp->key);
		new->value = ft_strdup(tmp->value);
		new->print = tmp->print;
		if (tmp->next)
		{
			new->next = ft_calloc(1, sizeof(t_env));
			new = new->next;
		}
		tmp = tmp->next;
	}
	return (head);
}

int	ft_export(t_lst *mnsh, char **str)
{
	int		i;
	t_env	*cpy;
	int		err;

	i = 1;
	if (!str[1])
	{
		if (!mnsh->env_var_lst)
			return (ERROR);
		cpy = cpy_env_var(mnsh->env_var_lst);
		sort_in_ascii(cpy);
		print_list_export(cpy);
		mnsh->exit_code = 0;
		delete_all_nodes_env(&cpy);
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
