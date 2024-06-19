/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:22 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/19 08:35:53 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit_code(t_lst *mnsh)
{
	if (WIFEXITED(mnsh->exit_code))
		return (mnsh->exit_code = WEXITSTATUS(mnsh->exit_code));
	else if (WIFSIGNALED(mnsh->exit_code))
		return (mnsh->exit_code = WTERMSIG(mnsh->exit_code) + 128);
	else if (WIFSTOPPED(mnsh->exit_code))
		return (mnsh->exit_code = WSTOPSIG(mnsh->exit_code));
	return (0);
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

int	get_nbargs(char **str)
{
	int	size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}

int	get_position_of_next_meta(char *input)
{
	int	i;
	int	minus_position;

	i = 0;
	minus_position = -1;
	while (input[i])
	{
		if (ft_ismeta(input[i]))
		{
			if (minus_position == -1)
				minus_position = i;
			else if (i < minus_position)
				minus_position = i;
			if (input[i] == 0)
				minus_position = i;
		}
		i++;
	}
	if (minus_position == -1)
		minus_position = i;
	return (minus_position);
}
