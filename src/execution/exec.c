/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/20 11:17:33 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	main_loop(t_cli *cli, int count)
{
	if (cli->com->type == COMMAND)
	{
		if (!cli->com->next)
			execute_last_command(cli);
		else
		{
			pipe(cli->mnsh->fd);
			piping(cli, count);
		}
		cli->mnsh->heredoc_pipe = 0;
		cli->mnsh->outfile_check = 0;
		cli->mnsh->infile_check = 0;
	}
}

int	get_nb_pipes(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == CONTROLE_OPERATOR)
			count++;
		token = token->next;
	}
	return (count);
}

void	handle_heredoc(t_cli *cli, int *heredoc)
{
	if (ft_heredoc(cli) == ERROR)
		exit(ERROR);
	else if (cli && cli->com && cli->com->command != NULL)
	{
		cli->mnsh->heredoc_backup_fd = open("/tmp/.heredoc", O_RDONLY);
		cli->mnsh->heredoc_pipe = 1;
		*heredoc = 1;
	}
	else
	{
		delete_file("/tmp/.heredoc", cli);
		exit(SUCCESS);
	}
}

void	loop_commands(t_cli *cli, int *count)
{
	t_com	*head;

	head = cli->com;
	if (!cli->com->command)
		handle_redirection(&cli);
	while (cli->com)
	{
		if (check_before_exec(&cli, count) == ERROR)
			break ;
		main_loop(cli, *count);
		cli->mnsh->file_check = 0;
		if (!cli->com->next)
			break ;
		cli->com = cli->com->next;
		(*count)++;
	}
	cli->com = head;
}

int	exec_pipe(t_cli *cli)
{
	int	count;
	int	heredoc;

	count = 0;
	handle_sig(2);
	heredoc = 0;
	cli->mnsh->pipe_count = get_nb_pipes(cli->token);
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	cli->mnsh->backup[0] = dup(STDIN_FILENO);
	cli->mnsh->backup[1] = dup(STDOUT_FILENO);
	if (cli->mnsh->nb_heredoc > 0)
		handle_heredoc(cli, &heredoc);
	loop_commands(cli, &count);
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (heredoc == 1)
		delete_file("/tmp/.heredoc", cli);
	dup2(cli->mnsh->backup[0], STDIN_FILENO);
	close(cli->mnsh->backup[0]);
	dup2(cli->mnsh->backup[1], STDOUT_FILENO);
	close(cli->mnsh->backup[1]);
	return (SUCCESS);
}
