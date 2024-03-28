/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/27 17:30:00 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_number_of_heredoc(char **input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], "<<", 2))
			j++;
		i++;
	}
	return (j);
}

int ft_heredoc(char **str)
{
	char *input;
	int i;
	pid_t pid;
	int count;

	count = 0;
	i = 0;
	if (!str[1])
	{
		printf("heredoc: syntax error\n");
		g_value = 2;
		return (ERROR);
	}
	if (check_number_of_heredoc(str) >= 16)
	{	
		printf("minishell : maximum here-document count exceeded\n");
		return (ERROR);
	}
	i = check_number_of_heredoc(str) + 1;
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
			if (!ft_strncmp(input, str[i], ft_strlen(str[i]))
				&& ft_strlen(str[i]) == ft_strlen(input))
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
