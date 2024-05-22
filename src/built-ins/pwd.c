/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:28:43 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/22 15:32:42 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_lst *mnsh, t_cli *cli)
{
	char	*path;

	path = search_path("PWD", mnsh);
	printf("%s\n", path);
	ft_exitcode(cli, 0);
	return (0);
}
