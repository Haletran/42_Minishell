/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:10:30 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/27 16:08:33 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	search_path(char *str, t_lst *args)
{
	int		i;
	char	**var = NULL;

	i = 0;
	if (!str)
		return (ERROR);
	while (args->env_var[i])
	{
		if (!ft_strncmp(args->env_var[i], str, ft_strlen(str)))
		{
			if (getenv(str) != NULL)
			{
				printf("%s", getenv(str));
				free_tab(var);
				var = NULL;
				return (SUCCESS);
			}
			else
			{
				var = ft_split(args->env_var[i], '=');
				printf("%s", var[1]);
				free_tab(var);
				var = NULL;
				return (SUCCESS);
			}
		}
		i++;
	}
	printf("\n");
	return (ERROR);
}

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

int	ft_echo(char **str, t_lst *args)
{
	int		i;
	char	**var;
	int		check;
	int		flag;

	i = 1;
	check = 1;
	flag = 0;
	var = malloc(sizeof(char **));
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
			printf("%d", g_value);
		else if (!ft_strncmp(str[i], "$", 1))
		{
			var = ft_split(str[i], '$');
			if (ft_strlen(str[1]) > 1)
			{
				if (var[0])
					search_path(var[0], args);
			}
			else
				printf("$");
			break ;
		}
		else if (!ft_strncmp(str[i], "*", 1))
			print_current();
		else if (str[i + 1] == NULL)
			printf("%s", str[i]);
		else
			printf("%s ", str[i]);
		i++;
	}
	free_tab(var);
	free_tab(str);
	str = NULL;
	var = NULL;
	if (flag == 0)
		printf("\n");
	return (SUCCESS);
}
