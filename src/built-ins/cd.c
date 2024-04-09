/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:10:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 16:18:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_tilde(char **str, t_lst *lst)
{
	char	*tilde_path;
	int		valid;

	valid = 0;
	lst->home_path = get_env("HOME", lst);
	if (ft_strlen(str[1]) == 1)
	{
		lst->home_path = get_env("HOME", lst);
		if (!lst->home_path)
		{
			ft_printf_fd(2, "minishell : cd : HOME not set\n");
			return (ERROR);
		}
		chdir(lst->home_path);
	}
	else
	{
		str[1] = ft_strtrim(str[1], "~");
		tilde_path = ft_strjoin(lst->home_path, str[1]);
		valid = chdir(tilde_path);
		free(tilde_path);
	}
	return (valid);
}

static void	handle_old_path(char *curr_path, char *old_path)
{
	getcwd(curr_path, 1024);
	printf("%s\n", old_path);
	chdir(old_path);
}

char	*search_path(char *str, t_lst *lst)
{
	t_env	*env;

	env = lst->env_var_lst;
	if (!str)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str)) \
			&& ft_strlen(env->key) == ft_strlen(str))
			break ;
		env = env->next;
	}
	return (env->value);
}

static int	handle_arguments(char **str)
{
	if (get_nbargs(str) > 2)
	{
		ft_printf_fd(2,"cd : too many arguments\n");
		return (ERROR);
	}
	return (0);
}

int	ft_cd(char **str, t_lst *lst)
{
	int		valid;
	char	**var;
	char	*old_path;
	char	curr_path[1024];

	old_path = getenv("OLDPWD");
	valid = 0;
	if (handle_arguments(str) == ERROR)
		return (ERROR);
	else if (!str[1] || !ft_strncmp(str[1], "--", -1))
	{
		lst->home_path = get_env("HOME", lst);
		if (!lst->home_path)
		{
			ft_printf_fd(2, "minishell : cd : HOME not set\n");
			return (ERROR);
		}
		chdir(lst->home_path);
	}
	else if (!ft_strncmp(str[1], "~", 1) && ft_strlen(str[1]) >= 1)
		handle_tilde(str, lst);
	else if (!ft_strncmp(str[1], "-", 1) && ft_strlen(str[1]) == 1)
		handle_old_path(curr_path, old_path);
	else if (!ft_strncmp(str[1], "$", 1) && ft_strlen(str[1]) >= 1)
	{
		var = ft_split(str[1], '$');
		valid = chdir(search_path(var[0], lst));
		free_tab(var);
		var = NULL;
	}
	else
	{
		getcwd(curr_path, 1024);
		ft_strcpy(old_path, curr_path);
		valid = chdir(str[1]);
	}
	if (valid)
	{
		perror(str[1]);
		return (ERROR);
	}
	return (SUCCESS);
}
