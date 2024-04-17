/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/17 18:02:37 by bapasqui         ###   ########.fr       */
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
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
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
	free_tab(str);
	rl_clear_history();
	delete_all_nodes_env(&args->env_cpy_lst);
	delete_all_nodes_env(&args->env_var_lst);
	free_tab(args->env_var);
	free(args->current_path);
	free(args);
}

void free_char(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	free_cli(t_cli *cli)
{
	//free(cli->input);
/* 	if (cli->token->token)
		delete_all_nodes_token(&cli->token); */
	free_tab(cli->meta);
	free_tab(cli->redirect);
	free_tab(cli->control);
	free(cli);
}

