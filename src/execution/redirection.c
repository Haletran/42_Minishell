/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:37:54 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 16:33:14 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirection(t_cli **cli)
{
	t_redirection	*red;

	red = (*cli)->com->redirection;
	(*cli)->mnsh->file_check = 0;
	while (red)
	{
		if (red->type == IN)
		{
			if (handle_infile(red, (*cli)) == ERROR)
				return (ERROR);
		}
		else if (red->type == OUT || red->type == APPEND_OUT)
		{
			if (handle_outfile(red, (*cli)) == ERROR)
				return (ERROR);
		}
		red = red->next;
	}
	return (SUCCESS);
}

int	handle_error(int fd, t_cli *cli)
{
	(void)fd;
	if (errno == ENOENT)
	{
		cli->mnsh->file_check = 1;
		ft_printf_fd(2, "minishell: No such file or directory\n");
		cli->mnsh->exit_code = 1;
		return (ERROR);
	}
	else
	{
		cli->mnsh->file_check = 1;
		ft_printf_fd(2, "minishell: Permission denied\n");
		cli->mnsh->exit_code = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int	open_file(t_redirection *red)
{
	int	fd;

	if (access(red->file, F_OK) != -1)
	{
		if (red->type == APPEND_OUT)
			fd = open(red->file, O_RDWR | O_APPEND, 0640);
		else
			fd = open(red->file, O_RDWR | O_TRUNC, 0640);
	}
	else
	{
		if (red->type == APPEND_OUT)
			fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0640);
		else
			fd = open(red->file, O_RDWR | O_CREAT, 0640);
	}
	return (fd);
}

int	handle_outfile(t_redirection *red, t_cli *cli)
{
	int	fd;

	fd = open_file(red);
	if (fd == -1 && cli->mnsh->file_check == 0)
	{
		if (handle_error(fd, cli) == ERROR)
			return (ERROR);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cli->mnsh->outfile_check = 1;
	return (SUCCESS);
}

int	handle_infile(t_redirection *red, t_cli *cli)
{
	int	fd;

	fd = open(red->file, O_RDONLY, 0640);
	if (fd == -1 && cli->mnsh->file_check == 0)
	{
		if (handle_error(fd, cli) == ERROR)
			return (ERROR);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	cli->mnsh->infile_check = 1;
	return (SUCCESS);
}
