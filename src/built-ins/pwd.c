/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:28:43 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/12 12:13:33 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_lst *args)
{
	args->current_path = getcwd(args->current_path, 1024);
	ft_printf_fd(1, "%s\n", args->current_path);
	return (SUCCESS);
}
