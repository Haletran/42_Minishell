/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:08:47 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 13:49:58 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_and(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(str[i], '&'))
			return (1);
		i++;
	}
	return (0);
}

int	exec_and(char **str, t_lst *args)
{
	int		i;
	char	**tab;

	i = 0;
	while (str[i])
	{
		tab = ft_split(str[i], ' ');
		exec(tab, args);
		i++;
	}
	return (0);
}
