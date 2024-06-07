/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/04 21:32:45 by bapasqui         ###   ########.fr       */
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

/* void	global_free(t_lst *mnsh, char **str)
{
	free_tab(str);
	rl_clear_history();
	close(mnsh->history_fd);
	delete_all_nodes_env(&mnsh->env_cpy_lst);
	delete_all_nodes_env(&mnsh->env_var_lst);
	free_tab(mnsh->env_var);
	free(mnsh->current_path);
	free(mnsh);
} */

void	freeway(t_cli *cli)
{
	delete_all_nodes_variable(&cli->variable);
	free_command_line(cli);
	close(cli->mnsh->history_fd);
	rl_clear_history();
	free_tab(cli->redirect);
	free_tab(cli->control);
	free_tab(cli->keyword);
	free_tab(cli->bracket);
	free_tab(cli->builtin);
	close_fds();
	delete_all_nodes_env(&cli->mnsh->env_var_lst);
	free(cli->mnsh->current_path);
	free_tab(cli->mnsh->env_var);
	free_char(cli->mnsh->env_path);
	free(cli->mnsh);
	free(cli);
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
	cli->input = free_char(cli->input);
	cli->n_dquote = 0;
	cli->n_quote = 0;
	cli->n_token = 0;
	cli->heredoc = 0;
}
