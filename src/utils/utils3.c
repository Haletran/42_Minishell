/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:25 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/17 16:13:42 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_path(char *str, t_lst *mnsh, int choose)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	if (!str)
		return (ERROR);
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
		{
			if (choose == 0)
				ft_printf_fd(1, "%s", env->value);
			else if (choose == 1)
				ft_printf_fd(2, "minishell : %s : No such file or directory\n",
					env->value);
			return (SUCCESS);
		}
		else
			env = env->next;
	}
	return (ERROR);
}

char	*get_env(char *str, t_lst *mnsh)
{
	t_env	*env;

	env = mnsh->env_var_lst;
	if (!str)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
			return (env->value);
		else
			env = env->next;
	}
	return (NULL);
}

int	count_pipe(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}

int	check_if_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}

void	historyze(t_cli *cli)
{
	char	*line;
	int		fd;
	char	*h_line;

	fd = dup(cli->mnsh->history_fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		h_line = ft_substr(line, 0, ft_strlen(line) - 1);
		if (!h_line)
		{
			free(line);
			freeway(cli);
		}
		add_history(h_line);
		free(line);
		free(h_line);
	}
	close(fd);
}
