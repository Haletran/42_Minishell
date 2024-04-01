/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:49 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/01 17:24:42 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_str(char **src)
{
	char	*dest;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	j = 0;
	dest = malloc(sizeof(dest) * get_nbargs(src));
	while (src[i][j])
	{
		dest[k] = src[i][j];
		k++;
		j++;
	}
	j = 0;
	i++;
	dest[k++] = '=';
	while (src[i][j])
	{
		dest[k] = src[i][j];
		k++;
		j++;
	}
	dest[k] = '\0';
	return (dest);
}

void	add_var_no_input(t_lst *args, char **str)
{
	int	len_env;

	len_env = 0;
	while (args->env_cpy[len_env])
		len_env++;
	args->env_cpy[len_env] = str[1];
	return ;
}

void	add_var(t_lst *args, char **str)
{
	char	**to_add;
	char	*stock;
	int		len_env;
	int		args_len;
	int		len_env_cpy;
	int		i;

	i = 1;
	len_env_cpy = 0;
	len_env = 0;
	while (args->env_var[len_env])
		len_env++;
	while (args->env_cpy[len_env_cpy])
		len_env_cpy++;
	while (str[i])
	{
		to_add = ft_split(str[i], '=');
		args_len = 0;
		while (to_add[args_len])
			args_len++;
		stock = make_str(to_add);
		args->env_var[len_env] = stock;
		args->env_cpy[len_env_cpy] = stock;
		len_env++;
		len_env_cpy++;
		i++;
	}
}

int	already_exist(t_lst *args, char **str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(str[1], '=');
	while (args->env_var[i])
	{
		if (!ft_strncmp(args->env_var[i], tmp[0], ft_strlen(tmp[1])))
			return (i);
		i++;
	}
	free(tmp);
	return (0);
}

int	ft_export(t_lst *args, char **str)
{
	int	i;

	i = 0;
	if (!args->env_var)
		return (ERROR);
	if (!str[1])
	{
		if (!args->env_cpy)
			return (ERROR);
		sort_in_ascii(args->env_cpy);
		while (args->env_cpy[i])
			printf("declare -x %s\n", args->env_cpy[i++]);
		return (1);
	}
	if (check_if_alpha(str[1]) == ERROR)
	{
		printf("minishell : %s not a valid identifier\n", str[1]);
		g_value = 1;
		return (ERROR);
	}
	if (!ft_strchr(str[1], '='))
	{
		i = already_exist(args, str);
		if (i >= 1)
			delete(args, i);
		add_var_no_input(args, str);
	}
	else
	{
		i = already_exist(args, str);
		if (i >= 1)
			delete(args, i);
		add_var(args, str);
	}
	return (SUCCESS);
}
