/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:15:28 by baptiste          #+#    #+#             */
/*   Updated: 2024/04/09 16:05:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Init different path value
 *
 * @param args
 */
void	init_lst(t_lst *args, char **envp)
{
	if (!envp || !*envp || check_if_path(envp) == 0)
	{
		ft_printf_fd(2, "Error: No environment variable found\n");
		exit(1);
	}
	args->env_var = ft_calloc(1, sizeof(char) * get_len(envp));
	args->env_var_lst = init_stack(args->env_var_lst, envp);
	args->env_cpy_lst = init_stack(args->env_cpy_lst, envp);
	ft_cpy(args->env_var, envp);
	args->exit_code = 0;
}

/**
 * @brief Init stack
 *
 * @param env
 * @param str
 * @return t_env*
 */
t_env *init_stack(t_env *env, char **str)
{
	char **tmp;
	char *value;
	char *key;
	int i;
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		tmp = ft_split(str[i], '=');
		value = ft_strdup(tmp[1]);
		key = ft_strdup(tmp[0]);
		insert_env_end(&env, key, value);
		i++;
		free_tab(tmp);
		free(value);
		free(key);
	}
	return (env);
}


