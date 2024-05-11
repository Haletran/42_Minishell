/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:30:53 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/11 15:40:26 by bapasqui         ###   ########.fr       */
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
	else if (!ft_strncmp(str, "<<", 2) && ft_strlen(str) == 2)
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
		ft_printf_fd(2, "%s: No such file or directory\n", str);
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

void	find_path(t_env *env, t_lst *mnsh)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
		{
			mnsh->env_path = ft_strdup(env->value);
			break ;
		}
		else
			env = env->next;
	}
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
		ft_printf_fd(2, "%s : command not found\n", str);
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

int	get_nb_args(t_com *com)
{
	t_arg	*arg;
	int		nb_args;

	nb_args = 0;
	while (com)
	{
		arg = com->arg;
		while (arg)
		{
			nb_args++;
			arg = arg->next;
		}
		com = com->next;
	}
	return (nb_args);
}

int	get_nb_commands(t_com *com)
{
	int	nb_commands;

	nb_commands = 0;
	while (com)
	{
		nb_commands++;
		com = com->next;
	}
	return (nb_commands);
}

char *check_parsing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str, "./", 2))
		{
			if (access(str, F_OK | R_OK) == -1)
			{
				ft_printf_fd(2, "%s: No such file or directory\n", str);
				exit(127);
			}
			else
				str = ft_strrchr(str, '/');
		}
		i++;
	}
	return (str);
}



char	**recreate_commands(t_cli *cli, char **commands)
{
	t_com	*com;
	t_arg	*arg;
	int		i;
	int		len;

	i = 0;
	com = cli->com;
	len = get_nb_args(com) + get_nb_commands(com);
	commands = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (com->command)
		{
			if (!ft_strncmp(com->command, "./", 2))
			{
				cli->com->env_path = ft_strdup(com->command);
				commands[i] = ft_strdup(check_parsing(com->command));
			}
			else if (!ft_strncmp(com->command, "/", 1))
			{
				if (opendir(com->command) == NULL)
				{
					if (access(com->command, F_OK | R_OK) == -1)
					{
						ft_printf_fd(2, "minishell: %s: command not found\n", com->command);
						return (NULL);
					}
					cli->com->env_path = ft_strdup(com->command);
					commands[i] = ft_strdup(ft_strrchr(com->command, '/'));
				}
				else
				{
					ft_printf_fd(2, "minishell: %s: Is a directory\n", com->command);
					cli->mnsh->exit_code = 126;
					return (NULL);
				}
			}
			else
				commands[i] = ft_strdup(com->command);
		}
		arg = com->arg;
		if (!arg)
		{
			i++;
			break ;
		}
		while (arg)
		{
			i++;
			if (arg->arg)
				commands[i] = ft_strdup(arg->arg);
			arg = arg->next;
		}
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

