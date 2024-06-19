/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:38:15 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/19 08:59:41 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_process(int exit_code, t_cli *cli)
{
	ft_printf_fd(1, EXIT_MSG);
	freeway(cli);
	return (exit_code);
}
