/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 15:20:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_env **lst)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

void	global_free(t_lst *args, char **str)
{
	if (str)
		free_tab(str);
	delete_all_nodes_env(&args->env_cpy_lst);
	delete_all_nodes_env(&args->env_var_lst);
	free_tab(args->env_var);
	free(args->env_path);
	// free((*args)->home_path);
	free(args->current_path);
	free(args->path_command);
	free(args->backup);
	free(args);
	// free(*args);
	// free(*args);
}
