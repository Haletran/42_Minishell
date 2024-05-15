/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/15 11:35:25 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char *code, t_cli *cli, char **str)
{
	long int	exit_code;

	if (!code)
	{
		printf("exit\n");
		free_tab(str);
		freeway(cli);
		exit(0);
	}
	exit_code = ft_atoi(code);
	if (ft_strlen(code) > 0 && !ft_isdigit(code[0]))
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			code);
		free_tab(str);
		freeway(cli);
		exit(2);
	}
	printf("exit\n");
	free_tab(str);
	freeway(cli);
	exit(exit_code % 256);
}
