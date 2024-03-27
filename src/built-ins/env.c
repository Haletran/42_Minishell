/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:39 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/26 11:38:13 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **envp, char **str)
{
	int	i;

	i = 0;
	if (!envp || !str)
		return (1);
	if (ft_strlen(str[1]) > 0)
	{
		printf("env : '%s': No such file or directory\n", str[1]);
		g_value = 127;
		return (ERROR);
	}
	else
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	return (SUCCESS);
}
