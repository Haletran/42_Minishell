/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:30:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/08 16:12:41 by bapasqui         ###   ########.fr       */
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

void	freeway(t_cli *cli)
{
	delete_all_nodes_variable(&cli->variable);
	free_command_line(cli);
	rl_clear_history();
	cli->av = free_char(cli->av);
	free_tab(cli->redirect);
	free_tab(cli->control);
	free_tab(cli->keyword);
	free_tab(cli->bracket);
	free_tab(cli->builtin);
	free_tab(cli->spe_param);
	if (cli->mnsh->env_var_lst != NULL)
		delete_all_nodes_env(&cli->mnsh->env_var_lst);
	cli->mnsh->current_path = free_char(cli->mnsh->current_path);
	cli->mnsh->env_path = free_char(cli->mnsh->env_path);
	free(cli->mnsh);
	free(cli);
}

char	*free_char(char *str)
{
	if (!str)
		return (NULL);
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
	free_tab(cli->mnsh->env_var);
	cli->mnsh->env_var = NULL;
	if (cli->flag_dquote == 1 || cli->flag_quote == 1)
	{
		cli->flag_dquote = 0;
		cli->flag_quote = 0;
		ft_printf_fd(2, "minishell: quotes not closed\n");
		cli->mnsh->exit_code = 2;
	}
	cli->n_dquote = 0;
	cli->n_quote = 0;
	cli->n_token = 0;
	cli->heredoc = 0;
}
