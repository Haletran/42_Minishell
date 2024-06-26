/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:14:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/26 11:38:59 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_eof(char *input, int line_count, t_com *com, t_cli *cli)
{
	ft_printf_fd(2, HEREDOC_EOF, line_count, com->command[1]);
	input = free_char(input);
	heredoc_close_fd(cli);
	ft_exitcode(cli, 0);
	return (input);
}

char	*handle_sigint(char *input, t_cli *cli)
{
	input = free_char(input);
	heredoc_close_fd(cli);
	ft_exitcode(cli, 130);
	return (input);
}

void	write_to_heredoc(char *input, t_cli *cli)
{
	ft_putstr_fd(input, cli->mnsh->heredoc_fd);
	ft_putstr_fd("\n", cli->mnsh->heredoc_fd);
}

char	*handle_heredoc_end(char *input, t_cli *cli)
{
	if (!cli->mnsh->nb_heredoc - 1)
		close(cli->mnsh->heredoc_fd);
	input = free_char(input);
	ft_exitcode(cli, 0);
	return (input);
}

void	child_process(t_cli *cli, t_com *com)
{
	char	*input;
	int		line_count;

	input = NULL;
	line_count = 0;
	while (1)
	{
		input = readline("> ");
		if (!input && !g_var)
			input = handle_eof(input, line_count, com, cli);
		if (g_var == 1)
			input = handle_sigint(input, cli);
		if (!cli->mnsh->nb_heredoc - 1 && ft_strncmp(input, com->command[1],
				ft_strlen(com->command[1])))
			write_to_heredoc(input, cli);
		if (!ft_strncmp(input, com->command[1], ft_strlen(com->command[1])))
			input = handle_heredoc_end(input, cli);
		input = free_char(input);
		line_count++;
	}
	input = free_char(input);
	cli->mnsh->heredoc_pipe = 2;
	ft_exitcode(cli, 0);
}
