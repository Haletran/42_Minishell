/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:54:32 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/01 20:29:56 by bapasqui         ###   ########.fr       */
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
		exit(ERROR);
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

void	print_all_com(t_com *com)
{
	t_com	*tmp;

	tmp = com;
	while (tmp)
	{
		ft_printf_fd(1, "index: %d\n", tmp->index);
		if (tmp->command)
			ft_printf_fd(1, "command: %s\n", tmp->command[0]);
		if (tmp->env_path)
			ft_printf_fd(1, "env_path: %s\n", tmp->env_path);
		if (tmp->type == HEREDOC)
			ft_printf_fd(1, "type: HEREDOC\n");
		if (tmp->type == COMMAND)
			ft_printf_fd(1, "type: COMMAND\n");
		tmp = tmp->next;
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
		return (ERROR);
	cli->mnsh->pipe_count = get_nb_pipes(cli->token);
	cli->mnsh->nb_heredoc = check_number_of_heredoc(cli->com);
	cli->mnsh->backup[0] = dup(STDIN_FILENO);
	cli->mnsh->backup[1] = dup(STDOUT_FILENO);
	if (cli->mnsh->nb_heredoc > 0)
		handle_heredoc(cli, &heredoc);
	if (g_var == 0)
		loop_commands(cli, &count);
	redirect_std(cli);
	wait_process();
	g_var = 0;
	if (heredoc == 1)
	{
		unlink("/tmp/.heredoc");
		close(cli->mnsh->heredoc_fd);
	}
	return (SUCCESS);
}
