/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:43:21 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/09 19:12:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	return_path(char *str, t_cli **cli)
{
	char	**path;
	int		i;
	char	*full_path;

	i = -1;
	find_path((*cli)->mnsh->env_var_lst, (*cli)->mnsh);
	if (!(*cli)->mnsh->env_path)
	{
		ft_printf_fd(2, "%s: No such file or directory\n", str);
		(*cli)->mnsh->exit_code = 127;
		return ;
	}
	path = ft_split((*cli)->mnsh->env_path, ':');
	while (path[++i])
	{
		full_path = ft_strjoin(path[i], "/");
		full_path = ft_strjoin_f(full_path, str);
		if (access(full_path, F_OK | R_OK) != -1)
			break ;
		full_path = free_char(full_path);
	}
	if (ft_error_path(str, path, (*cli)->mnsh, full_path) == EXIT_FAILURE)
		(*cli)->com->env_path = NULL;
	(*cli)->com->env_path = ft_strdup(full_path);
	full_path = free_char(full_path);
}

void	fill_command(t_cli *cli, t_token *tmp, t_com *com)
{
	int	j;

	j = 0;
	return_path(com->command, &cli);
	com->redirection = NULL;
	com->type = tmp->type;
	com->arg = NULL;
	com->pipe = 0;
	while (tmp)
	{
		if (tmp->type == ARGUMENT)
		{
			insert_arg_end(&com->arg, ft_strdup(tmp->token));
			j++;
		}
		else if (tmp->type == REDIRECTION_OPERATOR)
			com->redirection = ft_strdup(tmp->token);
		else if (tmp->type == CONTROLE_OPERATOR)
			com->pipe = 1;
		if (tmp->next == NULL)
			break ;
		else
			tmp = tmp->next;
	}
	com->n_arg = j;
}

void	create_command(t_cli *cli)
{
	t_token	*tmp;
	t_com	*com;
	int		i;

	i = 0;
	tmp = cli->token;
	while (tmp)
	{
		if (tmp->type == COMMAND || tmp->type == BUILTIN)
		{
			insert_com_end(&cli->com, ft_strdup(tmp->token), tmp->index);
			com = cli->com;
			fill_command(cli, tmp, com);
			i++;
		}
		tmp = tmp->next;
	}
}
