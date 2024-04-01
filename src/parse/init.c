/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:54:02 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/01 17:57:13 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Init different path value
 *
 * @param args
 */
void	init_lst(t_lst **args, char **envp)
{
	(*args)->home_path = getenv("HOME");
	(*args)->username = getenv("USER");
	(*args)->env_path = getenv("PATH");
	(*args)->env_var = malloc(sizeof(char) * get_len(envp));
	(*args)->env_cpy = malloc(sizeof(char) * get_len(envp));
	ft_cpy((*args)->env_var, envp);
	ft_cpy((*args)->env_cpy, envp);
	//(*args)->prompt = ft_join((*args)->username, "$> ");
	(*args)->exit_code = 0;
}
