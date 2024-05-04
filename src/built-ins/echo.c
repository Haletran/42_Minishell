/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:10:30 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:43:19 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_current(void)
{
	DIR				*dir;
	struct dirent	*cur;

	dir = opendir(".");
	if (dir != NULL)
	{
		cur = readdir(dir);
		while (cur != NULL)
		{
			if (cur->d_name[0] != '.')
				printf("%s ", cur->d_name);
			cur = readdir(dir);
		}
		closedir(dir);
	}
}

int	ft_echo(char **str, t_lst *mnsh)
{
	int		i;
	char	**var;
	int		check;
	int		flag;

	i = 1;
	check = 1;
	flag = 0;
	var = NULL;
	if (!str[1])
	{
		printf("\n");
		return (SUCCESS);
	}
	if (!ft_strncmp(str[i], "-n", 2))
	{
		while (str[1][check] == 'n')
			check++;
		if (check == (int)ft_strlen(str[1]))
		{
			flag++;
			i++;
		}
	}
	while (str[i])
	{
		if (!ft_strncmp(str[i], "$?", 2))
			ft_printf_fd(1, "%d", mnsh->exit_code);
		else if (!ft_strncmp(str[i], "$", 1))
		{
			if (ft_strlen(str[1]) > 1)
			{
				var = ft_split(str[i], '$');
				if (var[0])
					print_path(var[0], mnsh, 0);
			}
			else
				ft_printf_fd(1, "$");
		}
		else if (!ft_strncmp(str[i], "*", 1))
			print_current();
		else if (str[i + 1] == NULL)
			ft_printf_fd(1, "%s", str[i]);
		else
			ft_printf_fd(1, "%s ", str[i]);
		i++;
	}
	if (var)
		free_tab(var);
	if (flag == 0)
		printf("\n");
	return (SUCCESS);
}
