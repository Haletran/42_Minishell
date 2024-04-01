/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:10:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/01 18:23:31 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_tilde(char **str, t_lst *lst)
{
	char	*tilde_path;
	int		valid;

	str[1] = ft_strrchr(str[1], '~');
	tilde_path = ft_strjoin(lst->home_path, str[1]);
	valid = chdir(tilde_path);
	free(tilde_path);
	return (valid);
}

static void	handle_old_path(char *curr_path, char *old_path)
{
	getcwd(curr_path, 1024);
	printf("%s\n", old_path);
	chdir(old_path);
}

static char	*search_path(char *str, t_lst *lst)
{
	int		i;
	char	**var;

	var = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (lst->env_var[i])
	{
		if (!ft_strncmp(lst->env_var[i], str, ft_strlen(str))
			&& lst->env_var[i][ft_strlen(str)] == '=')
		{
			var = ft_split(lst->env_var[i], '=');
			break ;
		}
		i++;
	}
	return (var[1]);
}

static int	handle_arguments(char **str)
{
	if (get_nbargs(str) > 2)
	{
		printf("cd : too many arguments\n");
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
		chdir(lst->home_path);
	else if (!ft_strncmp(str[1], "~", 1) && ft_strlen(str[1]) >= 1)
		valid = handle_tilde(str, lst);
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
		perror(str[1]);
	return (SUCCESS);
}
