/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/17 12:43:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_code(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (ft_isdigit(code[i]) == FALSE)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	ft_exit(char *code, t_cli *cli)
{
	unsigned long long	exit_code;
	int					backup;

	backup = cli->mnsh->exit_code;
	if (!code)
	{
		ft_printf_fd(1, "exit\n");
		freeway(cli);
		exit(backup);
	}
	if (ft_strchr(code, ' '))
		code =	ft_strtrim(code, " ");
	if ((check_code(code) == ERROR || ft_strcmp(code,
				"9223372036854775808") >= 0 || ft_strcmp(code,
				"9223372036854775807") > 0))
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			code);
		freeway(cli);
		exit(2);
	}
	exit_code = ft_atoi(code);
	if (cli->com->command[2])
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		freeway(cli);
		exit(1);
	}
	printf("exit\n");
	freeway(cli);
	exit(exit_code % 256);
}

int	ft_exitcode(long int exit_code)
{
	if (!exit_code)
		exit(0);
	exit(exit_code % 256);
}
