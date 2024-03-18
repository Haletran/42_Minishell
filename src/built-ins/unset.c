/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:12:03 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 18:45:49 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int delete(t_lst *args, int len)
{
	int		i;
	int		after_len;
	char	**cpy;

	after_len = len;
	i = 0;
	while (args->env_var[after_len])
		after_len++;
	cpy = malloc(sizeof(cpy) * (len + after_len) + 1);
	while (i < len)
	{
		cpy[i] = args->env_var[i];
		i++;
	}
	len++;
	while (len < after_len)
	{
		cpy[i] = args->env_var[len];
		len++;
		i++;
	}
	args->env_var = cpy;
	args->env_cpy = cpy;
	return (SUCCESS);
}

int	ft_unset(char **str, t_lst *args)
{
	int	len;
	int i;

	len = 0;
	i = 1;
	while (str[i])
	{
		len = 0;
		while (args->env_var[len])
		{
			if (!ft_strncmp(args->env_var[len], str[i], ft_strlen(str[1])))
				break ;
			len++;
		}
		delete (args, len);
		i++;
	}
	return (SUCCESS);
}
