/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:43:21 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/02 16:01:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_path(char *str, t_cli **cli)
{
	char	*full_path;
	int		i;

	i = -1;
	if (!(*cli)->mnsh->env_path)
	{
		return (NULL);
	}
	while ((*cli)->path[++i])
	{
		full_path = ft_strjoin((*cli)->path[i], "/");
		full_path = ft_strjoin_f(full_path, str);
		if (access(full_path, F_OK | R_OK) != -1)
			break ;
		full_path = free_char(full_path);
	}
	if (ft_is_error_path(str, (*cli)->path, (*cli)->mnsh,
			full_path) == EXIT_FAILURE)
	{
		full_path = free_char(full_path);
		return (NULL);
	}
	return (full_path);
}

void	fill_command(t_cli *cli, t_token *tmp, t_com *com)
{
	int	i;
	int	arr_size;

	com->type = tmp->type;
	com->pipe = 0;
	i = 0;
	arr_size = get_nb_args(tmp);
	com->command = ft_calloc(arr_size + 1, sizeof(char *));
	while (i != arr_size)
	{
		if (tmp->token != NULL || !tmp->token)
			if (tmp->type != 2 && tmp->type != 13)
				com->command[i++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	com->command[i] = NULL;
	if (com->type == HEREDOC || com->type == REDIRECTION_OPERATOR
		|| com->command[0][0] == 0)
		com->env_path = NULL;
	else
		com->env_path = return_path(com->command[0], &cli);
}

char	**cpy_env(t_cli *cli)
{
	int		i;
	t_env	*tmp;
	char	*tmp2;
	char	**result;
	int		j;

	j = get_env_size(cli->mnsh->env_var_lst);
	tmp = cli->mnsh->env_var_lst;
	result = ft_calloc((j + 1), sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	tmp = cli->mnsh->env_var_lst;
	while (tmp)
	{
		if (tmp->value)
		{
			tmp2 = ft_strjoin(tmp->key, "=");
			result[i] = ft_strjoin_f(tmp2, tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}

void	init_ccs(t_ccs *ccs, t_cli *cli)
{
	ccs->index = 0;
	ccs->tmp = cli->token;
}

void	create_command(t_cli *cli)
{
	t_ccs	ccs;

	init_ccs(&ccs, cli);
	cli->mnsh->env_var = cpy_env(cli);
	find_path(cli->mnsh->env_var_lst, cli->mnsh);
	cli->path = ft_split(cli->mnsh->env_path, ':');
	while (ccs.tmp != NULL)
	{
		if (ccs.tmp->type == COMMAND || ccs.tmp->type == HEREDOC)
		{
			insert_com_end(&cli->com, ccs.tmp->type, ccs.index++);
			ccs.com = cli->com;
			while (ccs.com->next != NULL)
				ccs.com = ccs.com->next;
			fill_command(cli, ccs.tmp, ccs.com);
			ccs.com->redirection = NULL;
		}
		else if (ccs.tmp->type == CONTROLE_OPERATOR)
			ccs.index++;
		ccs.tmp = ccs.tmp->next;
	}
	create_redirection(cli);
	free_tab(cli->path);
	cli->mnsh->env_path = free_char(cli->mnsh->env_path);
}

int	get_nb_args(t_token *head)
{
	int		nb_args;
	int		heredoc_flag;
	t_token	*tmp;

	tmp = head;
	nb_args = 0;
	heredoc_flag = 0;
	while (tmp != NULL && tmp->type != CONTROLE_OPERATOR && heredoc_flag != 1)
	{
		if (tmp->type == DELIMITER)
			heredoc_flag = 1;
		else if (tmp->type == 2 || tmp->type == 13)
			nb_args--;
		nb_args++;
		if (tmp->next != NULL)
			if (tmp->next->type == HEREDOC)
				break ;
		tmp = tmp->next;
	}
	return (nb_args);
}
