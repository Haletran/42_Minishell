/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:30:53 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/15 08:11:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_path(t_env *env, t_lst *args)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
		{
			args->env_path = ft_strdup(env->value);
			break ;
		}
		else
			env = env->next;
	}
}

/**
 * @brief Path check if access is ok and loop until it test all path available
 *
 * @param str
 * @param args
 * @param nb
 * @return char*
 */
char	*check_path(char **str, t_lst *args, int nb)
{
	char	*cmd;
	char	**path;
	int		i;
	char	*tmp;
	char	*full_path;
	t_env	*env;

	i = 0;
	env = args->env_var_lst;
	cmd = str[nb];
	find_path(env, args);
	if (!args->env_path)
	{
		ft_printf_fd(2, "%s: No such file or directory\n", cmd);
		return (NULL);
	}
	path = ft_split(args->env_path, ':');
	tmp = ft_strjoin(path[i], "/");
	full_path = ft_strjoin(tmp, cmd);
	while (path[i])
	{
		if (access(full_path, F_OK | R_OK) != -1)
			break ;
		else
		{
			free_char(full_path);
			free_char(tmp);
			tmp = ft_strjoin(path[i], "/");
			full_path = ft_strjoin(tmp, cmd);
		}
		i++;
	}
	if (access(full_path, F_OK | R_OK) == -1)
	{
		perror(cmd);
		free_char(tmp);
		free_tab(path);
		free_char(full_path);
		args->exit_code = 127;
		return (NULL);
	}
	free_char(tmp);
	free_char(args->env_path);
	free_tab(path);
	return (full_path);
}

/**
 * @brief Execute the command after checking the path
 *
 * @param str
 * @param args
 * @param full_path
 * @return int
 */
int	exec_command(char **str, t_lst *args, char *full_path)
{
	pid_t	pid;

	args->env_var[get_nbargs(args->env_var)] = NULL;
	handle_sig(2);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
	{
		args->pid = &pid;
		if (execve(full_path, str, args->env_var) == -1)
		{
			if (!ft_strncmp(str[0], ";", 1) && ft_strlen(str[0]) == 1)
				ft_printf_fd(2,
					"minishell: syntax error near unexpected token `;'\n");
			else if (!ft_strncmp(str[0], "|", 1) && ft_strlen(str[0]) == 1)
				ft_printf_fd(2,
					"minishell: syntax error near unexpected token `|'\n");
			else
				ft_printf_fd(2, "minishell: %s: command not found\n", str[0]);
			args->exit_code = 127;
			free_tab(str);
			free(full_path);
			exit(127);
		}
	}
	get_exit_code(args);
	waitpid(pid, &g_value, 0);
	// free_tab(str);
	free(full_path);
	return (SUCCESS);
}

/**
 * @brief Main execution ft, check command path and execute
 *
 * @param str
 * @param args
 * @return int
 */
int	exec(char **str, t_lst *args)
{
	char	*full_path;
	char	*tmp;
	int		i;

	full_path = NULL;
	i = 0;
	if (!ft_strncmp(str[i], "./", 2))
	{
		if (access(str[i], F_OK) == 0)
		{
			full_path = str[i];
			str[i] = ft_strrchr(str[i], '/');
		}
		exec_command(str, args, full_path);
		return (SUCCESS);
	}
	else if (ft_strchr(str[i], '/'))
	{
		if (access(str[i], F_OK) == 0)
		{
			if (!ft_strncmp(str[0], "/", 1) && !ft_isalpha(str[0][1]))
			{
				ft_printf_fd(2, "minishell: %s: Is a directory\n", str[i]);
				return (ERROR);
			}
			full_path = str[i];
			tmp = ft_strrchr(str[i], '/');
			str[i] = ft_strdup(tmp);
			exec_command(str, args, full_path);
			return (SUCCESS);
		}
		else
		{
			perror(str[i]);
			args->exit_code = 127;
			free_tab(str);
			return (127);
		}
	}
	if (check_commands(str, args) == NOT_FOUND)
	{
		full_path = check_path(str, args, 0);
		if (full_path == NULL)
		{
			free_char(full_path);
			return (ERROR);
		}
		exec_command(str, args, full_path);
	}
	return (SUCCESS);
}
