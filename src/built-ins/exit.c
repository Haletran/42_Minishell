/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:16:58 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/01 14:53:46 by bapasqui         ###   ########.fr       */
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
			if (!(str[0] == '-' && result == 922337203685477580 && (str[i]
						- '0') == 8))
				return (++flag);
		result = result * 10 + (str[i++] - '0');
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
	return (result * sign);
}

int	ft_exit(char *code, t_cli *cli)
{
	long long	exit_code;
	int			backup;

	backup = cli->mnsh->exit_code;
	if (!code)
	{
		if (cli->mnsh->outfile_check == 1)
			backup = 0;
		exit(ft_exit_process(backup, cli));
	}
	exit_code = ft_strtoll(code);
	if (code[0] == '\0' || check_code(code) == ERROR
		|| ft_strtoll_check(code) > 0)
	{
		ft_printf_fd(2, EXIT_NUM_REQ, code);
		exit(ft_exit_process(2, cli));
	}
	if (cli->com->command[2])
	{
		ft_printf_fd(2, EXIT_TOO_MANY);
		cli->mnsh->exit_code = 1;
		return (1);
	}
	ft_main_exit(cli, exit_code);
	return (0);
}

int	ft_exitcode(t_cli *cli, long int exit_code)
{
	close(cli->mnsh->backup[1]);
	close(cli->mnsh->backup[0]);
	freeway(cli);
	if (!exit_code)
		exit(0);
	exit(exit_code % 256);
}
