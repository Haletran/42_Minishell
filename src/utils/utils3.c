/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:25 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/03 17:30:56 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_path(char *str, t_lst *args, int choose)
{
	t_env	*env;

	env = *args->env_var_lst;
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
