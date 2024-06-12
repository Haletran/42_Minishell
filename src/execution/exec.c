/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/12 12:10:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	main_loop(t_cli *cli, int count)
{
	if (cli->com->type == COMMAND)
	{
		if (count != 0)
		{
			cli->mnsh->prev_fd[0] = cli->mnsh->fd[0];
			if (cli->mnsh->outfile_check != 1)
			{
				dup2(cli->mnsh->prev_fd[0], STDIN_FILENO);
				close(cli->mnsh->prev_fd[0]);
			}
		}
		if (!cli->com->next)
			execute_last_command(cli);
		else
		{
			pipe(cli->mnsh->fd);
			piping(cli, count);
		}
		cli->mnsh->heredoc_pipe = 0;
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

static void	handle_heredoc(t_cli *cli, int *heredoc)
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

static void	loop_commands(t_cli *cli, int *count)
{
	//debug(cli, "exec_pipe");
	while (cli->com)
	{
		if (parsing_check(cli) == ERROR)
		{
			close(cli->mnsh->backup[0]);
			close(cli->mnsh->backup[1]);
			break ;
		}
		if (handle_redirection(&cli) == ERROR)
		{
			if (cli->com->next)
				cli->com = cli->com->next;
			else
				break;
		}
		check_error(&cli);
		main_loop(cli, *count);
		cli->mnsh->outfile_check = 0;
		cli->mnsh->infile_check = 0;
		cli->mnsh->file_check = 0;
		if (cli->com->next)
			cli->com = cli->com->next;
		else
			break ;
		(*count)++;
	}
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
	close_fds();
	return (SUCCESS);
}
