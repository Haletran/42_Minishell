/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 18:48:07 by bapasqui         ###   ########.fr       */
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
	args->exit_code = ft_atoi(code);
	exit_code = args->exit_code;
	printf("exit\n");
	exit(exit_code);
}
