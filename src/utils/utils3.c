/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:25 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 19:30:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_path(char *str, t_lst *args, int choose)
{
	t_env	*env;

	env = args->env_var_lst;
	if (!str)
		return (ERROR);
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
		{
			if (choose == 0)
				ft_printf_fd(1, "%s ", env->value);
			else if (choose == 1)
				ft_printf_fd(2, "minishell : %s : No such file or directory\n",
					env->value);
			return (SUCCESS);
		}
		else
			env = env->next;
	}
	return (ERROR);
}

char *get_env(char *str, t_lst *args)
{
	t_env	*env;

	env = args->env_var_lst;
	if (!str)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& ft_strlen(env->key) == ft_strlen(str))
			return (env->value);
		else
			env = env->next;
	}
	return (NULL);
}

int count_pipe(char **str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}


