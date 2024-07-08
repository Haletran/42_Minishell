/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/08 19:16:02 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	main_loop(t_cli *cli, int count)
{
	if (cli->com->type == COMMAND)
	{
		if (!cli->com->next || cli->com->next->type == HEREDOC)
			execute_last_command(cli);
		else
		{
			if (sigpipe_checker(cli->com->next) == ERROR)
				signal(BUILTINS_FREE, SIG_IGN);
			pipe(cli->mnsh->fd);
			piping(cli, count);
		}
		signal(BUILTINS_FREE, SIG_DFL);
		reset_redir_values(cli);
	}
	else if (cli->com->type == HEREDOC)
		heredoc_redirection(cli);
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
		exit (ERROR);
	else if (cli && cli->com && cli->com->command != NULL)
	{
		cli->mnsh->heredoc_backup_fd = open("/tmp/.heredoc", O_RDONLY);
		cli->mnsh->heredoc_pipe = 1;
		*heredoc = 1;
	}
	else
	{
		heredoc_close_fd(cli);
		unlink("/tmp/.heredoc");
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
		if (check_before_exec(&cli) != ERROR)
			main_loop(cli, *count);
		cli->mnsh->file_check = 0;
		if (!cli->com->next)
			break ;
		cli->com = cli->com->next;
		cli->com->prev = delete_node_com(&head, cli->com->prev);
		(*count)++;
	}
	cli->com = head;
	free_command_line(cli);
}

int	exec_pipe(t_cli *cli)
{
	int	count;
	int	heredoc;

	count = 0;
	handle_sig(2);
	heredoc = 0;
	if (check_er(cli) == ERROR)
	{
		if (!cli->com || !cli->com->redirection)
			return (ERROR);
	}
	cli->mnsh->pipe_count = get_nb_pipes(cli->token);
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	cli->mnsh->backup[0] = dup(STDIN_FILENO);
	cli->mnsh->backup[1] = dup(STDOUT_FILENO);
	if (cli->mnsh->nb_heredoc > 0)
		handle_heredoc(cli, &heredoc);
	if (g_var == 0)
		loop_commands(cli, &count);
	redirect_std(cli, heredoc);
	wait_process();
	cli->mnsh->heredoc_pipe = 0;
	return (SUCCESS);
}
