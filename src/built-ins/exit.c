/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/04 23:09:44 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char *code, t_lst *args)
{
	int	exit_code;

	exit_code = 0;
	if (!code)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(code) > 0 && !ft_isdigit(code[0]))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", code);
		exit(2);
	}
	if (ft_strlen(code) > 10)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", code);
		exit(2);
	}
	args->exit_code = ft_atoi(code);
	exit_code = args->exit_code;
	printf("exit\n");
	exit(exit_code);
}
