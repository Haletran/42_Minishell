/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/27 12:41:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_heredoc(char **str)
{
	char	*input;
	int		count;
	pid_t	pid;

	count = 0;
	if (!str[1])
	{
		printf("heredoc: syntax error\n");
		g_value = 2;
		return (ERROR);
	}
	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
	{
		handle_sig(1);
		while (1)
		{
			input = readline("> ");
			if (!input)
			{
				free(input);
				printf("warning: here-document at line %d delimited by end-of-file (wanted %s)\n", count, str[1]);
				exit(1);
			}
			if (!ft_strncmp(input, str[1], ft_strlen(str[1]))
				&& ft_strlen(str[1]) == ft_strlen(input))
			{
				free(input);
				break ;
			}
			count++;
			free(input);
		}
		exit(1);
	}
	else
		waitpid(pid, &g_value, 0);
	return (SUCCESS);
}
