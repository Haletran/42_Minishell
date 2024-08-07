/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:12:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/08 19:12:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_close_fd(t_cli *cli)
{
	if (cli->mnsh->heredoc_fd != -1)
		close(cli->mnsh->heredoc_fd);
	close(cli->mnsh->backup[0]);
	close(cli->mnsh->backup[1]);
}

int	check_number_of_heredoc(t_com *com)
{
	int		count;
	t_com	*tmp;

	count = 0;
	tmp = com;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	check_heredoc_error(t_cli *cli)
{
	t_com	*tmp;

	tmp = cli->com;
	while (tmp)
	{
		if (ft_strncmp(tmp->command[0], "<<", 2) == 0 && !tmp->command[1])
		{
			ft_printf_fd(2, HEREDOC_SYNT);
			return (ERROR);
		}
		tmp = tmp->next;
	}
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	if (cli->mnsh->nb_heredoc >= 13)
	{
		ft_printf_fd(2, HEREDOC_MAX);
		return (ERROR);
	}
	return (SUCCESS);
}
