/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:45:37 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/02 15:00:21 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_process(int exit_code, char *old_path, t_lst *lst)
{
	free(old_path);
	lst->exit_code = exit_code;
	return (exit_code);
}

int	cd_valid(int valid, char **str, char *old_path, t_lst *lst)
{
	if (valid == 10)
	{
		ft_printf_fd(2, OLD_PWD_NOT);
		return (return_process(1, old_path, lst));
	}
	else if (valid != 0)
	{
		perror(str[1]);
		return (return_process(1, old_path, lst));
	}
	update_path(lst, old_path);
	return (return_process(0, old_path, lst));
}
