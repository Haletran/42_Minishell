/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:22 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/19 11:48:34 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	get_exit_code(t_lst *args)
{
	if (WIFEXITED(args->exit_code))
		args->exit_code = WEXITSTATUS(args->exit_code);
	else if (WIFSIGNALED(args->exit_code))
		args->exit_code = WTERMSIG(args->exit_code) + 128;
	else if (WIFSTOPPED(args->exit_code))
		args->exit_code = WSTOPSIG(args->exit_code);
}

int	check_if_pipe(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(str[i], '|'))
			return (1);
		i++;
	}
	return (0);
}

char	**sort_in_ascii(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
