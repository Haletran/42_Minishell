/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:33:12 by bapasqui         ###   ########.fr       */
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

void	global_free(t_lst *mnsh, char **str)
{
	free_tab(str);
	rl_clear_history();
	close(mnsh->history_fd);
	delete_all_nodes_env(&mnsh->env_cpy_lst);
	delete_all_nodes_env(&mnsh->env_var_lst);
	free_tab(mnsh->env_var);
	free(mnsh->current_path);
	free(mnsh);
}

char	*free_char(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

void	free_command_line(t_cli *cli)
{
	delete_all_nodes_com(&cli->com);
	if (cli->token != NULL)
		delete_all_nodes_token(&cli->token);
	free(cli->input);
}
