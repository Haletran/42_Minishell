/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/16 15:10:26 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_number_of_heredoc(t_com *com)
{
	int	count;
	t_com *tmp;

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
	t_com *tmp;

	tmp = cli->com;
	while (tmp)
	{
		if (ft_strncmp(tmp->command[0], "<<", 2) == 0 && !tmp->command[1])
		{
			ft_printf_fd(2, "minishell: syntax error near unexpected token `newline'\n");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	if (cli->mnsh->nb_heredoc >= 13)
	{
		ft_printf_fd(2, "minishell: maximum here-document count exceeded\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	child_process(t_cli *cli, t_com *com)
{
	char	*input;
	int line_count;

	input = NULL;
	g_var = 0;
	line_count = 0;
	(void)cli;
	handle_sig(1);
	while (1)
	{
		input = readline("> ");
		if (!input && g_var == 0)
		{
						ft_printf_fd(2, "warning: here-document at line \
%d delimited by end-of-file (wanted '%s')\n", line_count, com->command[1]);
			exit(STOPPED);
		}
		if (g_var == 1)
			exit(ERROR);
		if (cli->mnsh->nb_heredoc - 1 == 0)
		{
			ft_putstr_fd(input, cli->mnsh->heredoc_fd);
			ft_putstr_fd("\n", cli->mnsh->heredoc_fd);
		}
		if (!ft_strncmp(input, com->command[1], ft_strlen(com->command[1])))
		{
			if (cli->mnsh->nb_heredoc - 1 == 0)
				close(cli->mnsh->heredoc_fd);
			exit(1);
		}
		line_count++;
	}
	input = free_char(input);
	freeway(cli);
	exit(SUCCESS);
}

int create_heredoc_file(t_cli **cli)
{
	(*cli)->mnsh->heredoc_fd = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_APPEND, 0777);
	if ((*cli)->mnsh->heredoc_fd == -1)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", strerror(errno), "/tmp/.heredoc");
		(*cli)->mnsh->exit_code = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int ft_heredoc(t_cli **cli)
{
	pid_t	pid;
	if (check_heredoc_error((*cli)) == ERROR)
	{
		(*cli)->mnsh->exit_code = 1;
		return (ERROR);
	}
	while ((*cli)->mnsh->nb_heredoc > 0)
	{
		if ((*cli)->mnsh->nb_heredoc - 1 == 0)
			if (create_heredoc_file(cli) == ERROR)
				return (ERROR);
		pid = fork();
		if (pid == -1)
			return (ERROR);
		else if (pid == 0)
			child_process((*cli), (*cli)->com);
		(*cli)->mnsh->nb_heredoc--;
		(*cli)->com = (*cli)->com->next;
	}
	while (waitpid(-1, &(*cli)->mnsh->exit_code, 0) > 0)
		;
    (*cli)->mnsh->exit_code = 0;
	close((*cli)->mnsh->heredoc_fd);
	return (SUCCESS);
}
