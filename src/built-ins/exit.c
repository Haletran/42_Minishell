/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/11 16:11:46 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char *code, t_lst *args, char **str)
{
	int	exit_code;

	if (!code)
	{
		printf("exit\n");
		global_free(args, str);
		exit(0);
	}
	exit_code = ft_atoi(code);
	if (ft_strlen(code) > 0 && !ft_isdigit(code[0]))
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			code);
		global_free(args, str);
		exit(2);
	}
	if (exit_code > 255 || ft_strlen(code) > 15)
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			code);
		global_free(args, str);
		exit(2);
	}
	printf("exit\n");
	global_free(args, str);
	exit(exit_code);
}
