/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:30:53 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/19 09:22:01 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_builtin(char *str)
{
	if (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == 3)
		return (SUCCESS);
	else if ((!ft_strncmp(str, "echo", 4) && ft_strlen(str) == 4)
		|| (!ft_strncmp(str, "e\"ch\"o", 5) && ft_strlen(str) == 6))
		return (SUCCESS);
	else if (!ft_strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		return (SUCCESS);
	else if (!ft_strncmp(str, "export", 6) && ft_strlen(str) == 6)
		return (SUCCESS);
	else if (!ft_strncmp(str, "unset", 5) && ft_strlen(str) == 5)
		return (SUCCESS);
	else if (!ft_strncmp(str, "env", 3) && ft_strlen(str) == 3)
		return (SUCCESS);
	else if (!ft_strncmp(str, "exit", 4) && ft_strlen(str) == 4)
		return (SUCCESS);
	return (ERROR);
}

char	*check_path(char *str, t_lst *mnsh)
{
	char	**path;
	int		i;
	char	*full_path;

	i = 0;
	find_path(mnsh->env_var_lst, mnsh);
	if (!mnsh->env_path)
	{
		print_error(NO_FILE, str);
		mnsh->exit_code = 127;
		return (NULL);
	}
	path = ft_split(mnsh->env_path, ':');
	full_path = ft_strjoin_f(ft_strjoin(path[i], "/"), str);
	while (path[i])
	{
		if (access(full_path, F_OK | R_OK) != -1)
			break ;
		full_path = free_char(full_path);
		full_path = ft_strjoin_f(ft_strjoin(path[i], "/"), str);
		i++;
	}
	if (ft_error_path(str, path, mnsh, full_path) == EXIT_FAILURE)
		return (NULL);
	return (full_path);
}

int	find_path(t_env *env, t_lst *mnsh)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
		{
			mnsh->env_path = ft_strdup(env->value);
			return (SUCCESS);
		}
		else
			env = env->next;
	}
	return (ERROR);
}

int	ft_error_path(char *str, char **path, t_lst *mnsh, char *full_path)
{
	if (full_path == NULL)
	{
		free_tab(path);
		mnsh->env_path = free_char(mnsh->env_path);
		full_path = free_char(full_path);
		if (check_if_builtin(str) == SUCCESS)
			return (EXIT_SUCCESS);
		mnsh->exit_code = 127;
		return (EXIT_FAILURE);
	}
	if (access(full_path, F_OK | R_OK) == -1)
	{
		if (check_if_builtin(str) == SUCCESS)
			return (EXIT_SUCCESS);
		print_error(NO_FILE, str);
		free_tab(path);
		mnsh->env_path = free_char(mnsh->env_path);
		full_path = free_char(full_path);
		mnsh->exit_code = 127;
		return (EXIT_FAILURE);
	}
	mnsh->env_path = free_char(mnsh->env_path);
	free_tab(path);
	return (EXIT_SUCCESS);
}

int	check_if_forked(t_cli *cli)
{
	if (cli->com->type == COMMAND)
	{
		if (!ft_strncmp(cli->com->command[0], "export", 6)
			&& ft_strlen(cli->com->command[0]) == 6)
			return (SUCCESS);
		else if (!ft_strncmp(cli->com->command[0], "unset", 5)
			&& ft_strlen(cli->com->command[0]) == 5)
			return (SUCCESS);
		else if (!ft_strncmp(cli->com->command[0], "cd", 2)
			&& ft_strlen(cli->com->command[0]) == 2)
			return (SUCCESS);
	}
	return (NOT_FOUND);
}
