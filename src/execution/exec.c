/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:30:53 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/19 15:36:11 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Associate commands to built-ins if needed
 *
 * @param str
 * @param args
 * @return int (true / false)
 */
int	check_commands(char **str, t_lst *args)
{
	if (!ft_strncmp(str[0], "pwd", 3) && ft_strlen(str[0]) == 3)
		return (pwd(args));
	else if (!ft_strncmp(str[0], "echo", 4) && ft_strlen(str[0]) == 4)
		return (ft_echo(str, args));
	else if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
		return (ft_cd(str, args));
	else if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
		return (ft_export(args, str));
	else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (ft_unset(str, args));
	else if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (ft_env(args->env_var, str));
	else if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
		return (ft_exit(str[1], args));
	else if (!ft_strncmp(str[0], "<<", 2) && ft_strlen(str[0]) == 2)
		return (ft_heredoc(str));
	return (NOT_FOUND);
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
	char	*full_path;

	cmd = str[nb];
	path = NULL;
	path = ft_split(args->env_path, ':');
	*path = ft_join(*path, "/");
	full_path = ft_join(*path, cmd);
	while (*path)
	{
		if (access(full_path, F_OK | R_OK) == 0)
			break ;
		else
		{
			*path = ft_join(*path, "/");
			full_path = ft_join(*path, cmd);
		}
		path++;
	}
	// free_tab(path);
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

	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
	{
		args->pid = &pid;
		if (execve(full_path, str, args->env_var) == -1)
		{
			perror(full_path);
			g_value = 127;
			free_tab(str);
			exit(127);
		}
	}
	signal(CTRL_C, sig_command_is_running);
	waitpid(pid, &g_value, 0);
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
			full_path = str[i];
			tmp = ft_strrchr(str[i], '/');
			str[i] = ft_strdup(tmp);
			exec_command(str, args, full_path);
			return (SUCCESS);
		}
		else
		{
			perror(str[i]);
			g_value = 127;
			// free_tab(str);
			return (127);
		}
	}
	if (check_commands(str, args) == NOT_FOUND)
	{
		full_path = check_path(str, args, 0);
		if (full_path == NULL)
			return (ERROR);
		exec_command(str, args, full_path);
	}
	return (SUCCESS);
}
