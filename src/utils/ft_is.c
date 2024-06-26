/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:55:55 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/26 15:43:33 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_ismeta(char c)
{
	int	i;

	i = 0;
	while (META_LIST[i])
	{
		if (c == META_LIST[i])
			return (c);
		i++;
	}
	return (0);
}

int	ft_iscontrol(char *token, t_cli *cli)
{
	int	j;

	j = 0;
	while (cli->control[j])
	{
		if (ft_strcmp(token, cli->control[j++]) == 0)
			return (1);
	}
	return (0);
}

int	ft_isredirect(char *token, t_cli *cli)
{
	int	i;

	i = 0;
	while (cli->redirect[i])
	{
		if (ft_strcmp(token, cli->redirect[i++]) == 0)
			return (1);
	}
	return (0);
}

int	ft_isthis(char *this, char c)
{
	int	i;

	i = 0;
	while (this[i])
	{
		if (c == this[i])
			return (c);
		i++;
	}
	return (0);
}

int	ft_is_error_path(char *str, char **path, t_lst *mnsh, char *full_path)
{
	(void)path;
	(void)mnsh;
	if (full_path == NULL)
	{
		free_char(full_path);
		return (EXIT_FAILURE);
	}
	if (access(full_path, F_OK | R_OK) == -1)
	{
		if (check_if_builtin(str) == SUCCESS)
			return (EXIT_SUCCESS);
		ft_printf_fd(2, "%s : command not found\n", str);
		free_char(full_path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
