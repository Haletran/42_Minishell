/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:10:30 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/26 15:35:13 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_n_option(char **str, int *i, int *flag)
{
	int	check;

	while (str[*i] && !ft_strncmp(str[*i], "-n", 2))
	{
		check = 1;
		while (str[*i][check] == 'n')
			check++;
		if (str[*i][check] == '\0')
		{
			(*flag)++;
			(*i)++;
		}
		else
			break ;
	}
	return (SUCCESS);
}

void	echo_print(char **str, int i)
{
	while (str[i])
	{
		if (str[i + 1] == NULL)
			ft_printf("%s", str[i]);
		else
			ft_printf("%s ", str[i]);
		i++;
	}
}

int	ft_echo(char **str, t_lst *mnsh, t_cli *cli)
{
	int	i;
	int	flag;

	(void)mnsh;
	i = 1;
	flag = 0;
	if (!str[1])
	{
		ft_printf_fd(1, "\n");
		mnsh->exit_code = 0;
		ft_exitcode(cli, 0);
	}
	handle_n_option(str, &i, &flag);
	echo_print(str, i);
	mnsh->exit_code = 0;
	if (flag == 0)
		ft_printf("\n");
	ft_exitcode(cli, 0);
	return (1);
}
