/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:39 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/15 21:24:43 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_lst *mnsh, char **str)
{
	if (!str)
		return (ERROR);
	if (ft_strlen(str[1]) > 0)
	{
		ft_printf_fd(2, "env : '%s': No such file or directory\n", str[1]);
		mnsh->exit_code = 127;
		return (ERROR);
	}
	else if (ft_strlen(str[1]) == 0)
		print_list_env("=", mnsh);
	mnsh->exit_code = 0;
	return (SUCCESS);
}
