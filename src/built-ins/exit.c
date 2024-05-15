/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/15 18:07:44 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char *code, t_cli *cli)
{
	long int	exit_code;

	if (!code)
	{
		printf("exit\n");
		freeway(cli);
		exit(0);
	}
	exit_code = ft_atoi(code);
	if (exit_code % 255 == 0 || (ft_strlen(code) > 0  && !ft_isdigit(code[0])))
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			code);
		freeway(cli);
		exit(2);
	}
	printf("exit\n");
	freeway(cli);
	exit(exit_code % 256);
}

int ft_exitcode(long int exit_code)
{
	if(!exit_code)
		exit(0);
	exit(exit_code % 256);
}
