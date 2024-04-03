/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:54:02 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/03 11:49:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_if_path(char **envp)
{
	int i;

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
void	init_lst(t_lst **args, char **envp)
{
	if (!envp || !*envp || check_if_path(envp) == 0)
	{
		printf("Error: No environment variable found\n");
		exit(1);
	}
	*args = malloc(sizeof(t_lst *) * 12);
	(*args)->home_path = getenv("HOME");
	(*args)->username = getenv("USER");
	(*args)->env_var = malloc(sizeof(char) * get_len(envp));
	(*args)->env_var_lst = malloc(sizeof(char) * get_len(envp));
	(*args)->env_cpy_lst = malloc(sizeof(char) * get_len(envp));
	init_stack(((*args)->env_var_lst), envp);
	init_stack(((*args)->env_cpy_lst), envp);
	ft_cpy((*args)->env_var, envp);
	//(*args)->prompt = ft_join((*args)->username, "$> ");
	(*args)->exit_code = 0;
}

/**
 * @brief Init stack
 *
 * @param env
 * @param str
 * @return t_env*
 */
void	init_stack(t_env **env, char **str)
{
	t_env	*head;
	int		tmp;

	head = NULL;
	tmp = 0;
	if (!str)
		return ;
	while (tmp != get_nbargs(str))
	{
		if (!(*env))
		{
			(*env) = ft_lst_new_2(str[tmp]);
			head = (*env);
		}
		else
		{
			while ((*env) && (*env)->next != NULL)
				(*env) = (*env)->next;
			ft_lstadd_back_2(*env, str[tmp]);
		}
		tmp++;
	}
	(*env) = head;
}

