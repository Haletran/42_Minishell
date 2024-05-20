/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/20 17:51:43 by bapasqui         ###   ########.fr       */
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

void	replace_var(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_var_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i]))
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

void	replace_var_cpy(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_cpy_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i]))
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

int	add_var_no_input(t_lst *mnsh, char **str, int i)
{
	t_env	*env;

	env = mnsh->env_cpy_lst;
	// check if alphae
	if (check_if_var_exist(env, str[i]))
		return (ERROR);
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	env->next->key = ft_strdup(str[i]);
	env->next->value = NULL;
	env->next->next = NULL;
	return (SUCCESS);
}

void	add_var2(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_cpy_lst;
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	if (!ft_strncmp(tmp[1], "$", 1))
	{
		env->next->value = expand_var(mnsh, ft_strdup(tmp[1]));
		env->next->next = NULL;
		free_tab(tmp);
		return ;
	}
	env->next->key = ft_strdup(tmp[0]);
	env->next->value = ft_strdup(tmp[1]);
	env->next->next = NULL;
	free_tab(tmp);
	return ;
}

void	add_var(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(str[i], '=');
	env = mnsh->env_var_lst;
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	env->next->key = ft_strdup(tmp[0]);
	if (!ft_strncmp(tmp[1], "$", 1))
	{
		env->next->value = expand_var(mnsh, ft_strdup(tmp[1]));
		env->next->next = NULL;
		add_var2(mnsh, str, i);
		free_tab(tmp);
		return ;
	}
	env->next->value = ft_strdup(tmp[1]);
	env->next->next = NULL;
	free_tab(tmp);
	add_var2(mnsh, str, i);
	return ;
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

int	add_back2(t_lst *mnsh, char **str, int i)
{
	t_env	*env;
	char	*value;
	char	*to_keep;
	char	**tmp;

	tmp = ft_split(str[i], '+');
	to_keep = ft_strtrim(tmp[1], "=");
	env = mnsh->env_cpy_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, tmp[0], ft_strlen(str[i])))
		{
			value = ft_strdup(env->value);
			env->value = free_char(env->value);
			env->value = ft_strjoin(value, to_keep);
			value = free_char(value);
			to_keep = free_char(to_keep);
			free_tab(tmp);
			return (SUCCESS);
		}
		env = env->next;
	}
	free_tab(tmp);
	to_keep = free_char(to_keep);
	return (ERROR);
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

int check_valid_identifier(char **str)
{
	char **tmp;
	int i = 0;

	tmp = ft_split(str[1], '=');
	if(!tmp[0])
		return (ERROR);
	while (tmp[0][i])
	{
		if (!ft_isalpha(tmp[0][i]) || tmp[0][i] == '-')
			return (ERROR);
		i++;
	}
	if (tmp[1])
	{
		if (ft_strlen(tmp[1]) == 0)
			return (ERROR);
	}
	return (SUCCESS);
}

//export HELLO=123 A- WORLD=456
int	ft_export(t_lst *mnsh, char **str)
{
	int	i;

	i = 1;
	if (!str[1])
	{
		if (!mnsh->env_cpy_lst)
			return (ERROR);
		sort_in_ascii(mnsh->env_cpy_lst);
		print_list_export(mnsh);
		mnsh->exit_code = 0;
		return(SUCCESS);
	}
	while (str[i])
	{
		if (check_valid_identifier(str) == ERROR)
		{
			ft_printf_fd(2, "minishell : export: '%s' not a valid identifier\n",
			str[1]);
			mnsh->exit_code = 1;
			return(mnsh->exit_code);
		}
		if (ft_strchr(str[i], '+'))
			add_back(mnsh, str, i);
		else if (ft_strchr(str[i], '=') && !already_exist(mnsh, str, i))
			add_var(mnsh, str, i);
		else if (!ft_strchr(str[i], '=') && !already_exist(mnsh, str, i))
			add_var_no_input(mnsh, str, i);
		else
		{
			replace_var(mnsh, str, i);
			replace_var_cpy(mnsh, str, i);
		}
		i++;
	}
	mnsh->exit_code = 0;
	return (mnsh->exit_code);
}
