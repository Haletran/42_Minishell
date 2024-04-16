/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/15 15:23:25 by bapasqui         ###   ########.fr       */
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

int	ft_heredoc(char **str, t_lst *args)
{
	char	*input;
	int		i;
	pid_t	pid;
	int		count;

	count = 0;
	(void)args;
	i = 0;
	input = NULL;
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
	i = check_number_of_heredoc(str);
	pid = fork();
	if (pid == -1)
	{
		free_tab(str);
		return (ERROR);
	}
	else if (pid == 0)
	{
		handle_sig(1);
		while (1)
		{
			input = readline("> ");
			if (!input && g_var == 0)
			{
				printf("warning: here-document at line \
%d delimited by end-of-file (wanted %s)\n",
						count,
						str[i]);
				free_char(input);
				exit(STOPPED);
			}
			if (g_var == 1)
			{
				free_char(input);
				exit(ERROR);
			}
			if (!ft_strncmp(input, str[i], ft_strlen(str[i]))
				&& ft_strlen(str[i]) == ft_strlen(input))
			{
				free_char(input);
				break ;
			}
			count++;
			free_char(input);
		}
		global_free(args, str);
		exit(SUCCESS);
	}
	waitpid(pid, &g_value, 0);
	free_char(input);
	return (SUCCESS);
}

