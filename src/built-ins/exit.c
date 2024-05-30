/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/30 14:11:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_code(char *code)
{
	int	i;

	i = 0;
	while (code[i] == ' ')
		i++;
	while (code[i])
	{
		if (ft_isdigit(code[i]) == FALSE)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

long long	ft_strtoll_check(const char *str)
{
	int			i;
	long long	result;
	int			flag;

	i = 0;
	flag = 0;
	result = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			flag++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (9223372036854775807 - (str[i] - '0')) / 10)
		{
			flag++;
			break ;
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (flag);
}

long long	ft_strtoll(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_exit(char *code, t_cli *cli)
{
	long long	exit_code;
	int			backup;

	backup = cli->mnsh->exit_code;
	if (!code)
	{
		ft_printf_fd(1, "exit\n");
		freeway(cli);
		exit(backup);
	}
	exit_code = ft_strtoll(code);
	if (ft_strtoll_check(code) > 0 || check_code(code) == ERROR)
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			code);
		freeway(cli);
		exit(2);
	}
	if (cli->com->command[2])
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		freeway(cli);
		exit(1);
	}
	ft_printf_fd(1, "exit\n");
	freeway(cli);
	exit(exit_code % 256);
}

int	ft_exitcode(t_cli *cli, long int exit_code)
{
	freeway(cli);
	if (!exit_code)
		exit(0);
	exit(exit_code % 256);
}
