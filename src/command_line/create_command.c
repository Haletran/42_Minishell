/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:43:21 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/13 12:24:57 by bapasqui         ###   ########.fr       */
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
		(*cli)->mnsh->exit_code = 127;
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
	if (is_error_path(str, (*cli)->path, (*cli)->mnsh,
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
		if (tmp->token != NULL)
			com->command[i++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	com->command[i] = NULL;
	if (com->type == HEREDOC || com->type == REDIRECTION_OPERATOR)
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

    j = 0;
    tmp = cli->mnsh->env_var_lst;
    while (tmp && ++j)
        tmp = tmp->next;
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

void	create_command(t_cli *cli)
{
	t_token	*tmp;
	t_com	*com;

	tmp = cli->token;
	cli->mnsh->env_var = cpy_env(cli);
	find_path(cli->mnsh->env_var_lst, cli->mnsh);
	cli->path = ft_split(cli->mnsh->env_path, ':');
	while (tmp != NULL)
	{
		if (tmp->type == COMMAND || tmp->type == BUILTIN
			|| tmp->type == HEREDOC)
		{
			insert_com_end(&cli->com, tmp->type, tmp->index);
			com = cli->com;
			while (com->next != NULL)
				com = com->next;
			fill_command(cli, tmp, com);
			com->redirection = NULL;
		}
		tmp = tmp->next;
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
	while (tmp != NULL && tmp->type != REDIRECTION_OPERATOR
		&& tmp->type != CONTROLE_OPERATOR && heredoc_flag != 1)
	{
		if (tmp->type == DELIMITER)
			heredoc_flag = 1;
		nb_args++;
		tmp = tmp->next;
	}
	return (nb_args);
}

void	delete_n_token(t_token **head, int n)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp != NULL && n != 0)
	{
		delete_node_token(head, tmp);
		n--;
	}
}
