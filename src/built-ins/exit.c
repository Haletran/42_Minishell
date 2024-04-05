/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/05 22:54:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char *code, t_lst *args)
{
	int exit_code;

	(void)args;
	exit_code = 0;
	if (!code)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(code) > 0 && !ft_isdigit(code[0]))
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", code);
		exit(2);
	}
	exit_code = ft_atoi(code);
	if (exit_code > 255 || ft_strlen(code) > 15)
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", code);
		exit(2);
	}
	//exit_code = args->exit_code;
	printf("exit\n");
	exit(exit_code);
}
