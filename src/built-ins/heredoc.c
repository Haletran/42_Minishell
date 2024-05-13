/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/13 16:54:16 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_number_of_heredoc(t_com *com)
{
	int	count;

	count = 0;
	while (com)
	{
		if (com->type == HEREDOC)
			count++;
		com = com->next;
	}
	return (count);
}

int	check_heredoc_error(t_cli *cli)
{
	int	i;
	t_com *tmp;

	i = 0;
	tmp = cli->com;
	while (tmp)
	{
		if (tmp->command[i] && !tmp->command[i + 1])
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	if (cli->mnsh->nb_heredoc >= 13)
	{
		printf("minishell: maximum here-document count exceeded\n");
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
						printf("warning: here-document at line \
%d delimited by end-of-file (wanted '%s')\n", line_count, com->command[1]);
			exit(STOPPED);
		}
		if (g_var == 1)
			exit(ERROR);
		if (!ft_strncmp(input, com->command[1], ft_strlen(com->command[1])))
			exit(1);
		line_count++;
	}
	input = free_char(input);
	freeway(cli);
	exit(SUCCESS);
}

int ft_heredoc(t_cli *cli)
{
	pid_t	pid;
	t_com *tmp;
	if (check_heredoc_error(cli) == ERROR)
	{
		cli->mnsh->exit_code = 1;
		return (ERROR);
	}
	tmp = cli->com;
	while (cli->mnsh->nb_heredoc > 0)
	{
		pid = fork();
		if (pid == -1)
			return (ERROR);
		else if (pid == 0)
			child_process(cli, tmp);
		cli->mnsh->nb_heredoc--;
		tmp = tmp->next;
		waitpid(pid, &cli->mnsh->exit_code, 0);
	}
	return (SUCCESS);
}
