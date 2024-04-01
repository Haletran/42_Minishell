/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:39 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/01 17:46:22 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **envp, char **str)
{
	int	i;

	i = 0;
	if (!envp || !str)
		return (ERROR);
	if (ft_strlen(str[1]) > 0)
	{
		printf("env : '%s': No such file or directory\n", str[1]);
		g_value = 127;
		return (ERROR);
	}
	else
		if (ft_strlen(str[1]) == 0)
			print_tab(envp);
	return (SUCCESS);
}
