/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:39:31 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_number_of_heredoc(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], "<<", 2) && !input[i + 1])
			break ;
		i++;
	}
	return (i - 1);
}

int	check_heredoc_error(char **str)
{
	if (!str[1])
	{
		printf("heredoc: syntax error\n");
		return (ERROR);
	}
	if (check_number_of_heredoc(str) >= 16)
	{
		printf("minishell : maximum here-document count exceeded\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	child_process(char **str, t_lst *mnsh)
{
	char	*input;
	int		i;
	int		count;

	count = 1;
	i = 1;
	input = NULL;
	handle_sig(1);
	while (1)
	{
		input = readline("> ");
		if (!input && g_var == 0)
		{
			printf("warning: here-document at line \
%d delimited by end-of-file (wanted '%s')\n",
					count,
					str[i]);
			free_char(input);
			global_free(mnsh, str);
			exit(STOPPED);
		}
		if (g_var == 1)
		{
			free_char(input);
			global_free(mnsh, str);
			exit(ERROR);
		}
		if (!ft_strncmp(input, str[i], ft_strlen(str[i]))
			&& ft_strlen(str[i]) == ft_strlen(input))
		{
			if (!str[i + 1])
			{
				free_char(input);
				break ;
			}
			i += 2;
		}
		count++;
		free_char(input);
	}
	global_free(mnsh, str);
	exit(SUCCESS);
}

int	ft_heredoc(char **str, t_lst *mnsh)
{
	char	*input;
	pid_t	pid;

	input = NULL;
	if (check_heredoc_error(str) == ERROR)
	{
		mnsh->exit_code = 1;
		return (ERROR);
	}
	pid = fork();
	if (pid == -1)
	{
		free_tab(str);
		return (ERROR);
	}
	else if (pid == 0)
		child_process(str, mnsh);
	waitpid(pid, &mnsh->exit_code, 0);
	/* 	if (str[2] && ft_strncmp(str[2], "<<", 2))
			exec_command(str + 2, mnsh, check_path(str + 2, mnsh)); */
	free_char(input);
	return (SUCCESS);
}
