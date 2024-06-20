/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_another.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:01:45 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/20 13:51:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_file(char *name, t_cli *cli)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		close(cli->mnsh->backup[0]);
		close(cli->mnsh->backup[1]);
		close(cli->mnsh->heredoc_fd);
		close(cli->mnsh->heredoc_backup_fd);
		execve("/bin/rm", (char *[]){"rm", "-rf", name, NULL},
			cli->mnsh->env_var);
		exit(1);
	}
}

t_env	*sort_in_ascii(t_env *list)
{
	t_env	*current;
	t_env	*index;
	char	*tmp_key;
	char	*tmp_value;

	current = list;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(current->key, index->key) > 0)
			{
				tmp_key = current->key;
				tmp_value = current->value;
				current->key = index->key;
				current->value = index->value;
				index->key = tmp_key;
				index->value = tmp_value;
			}
			index = index->next;
		}
		current = current->next;
	}
	return (list);
}

void	historyze(t_cli *cli)
{
	char	*line;
	int		fd;
	char	*h_line;

	fd = dup(cli->mnsh->history_fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		h_line = ft_substr(line, 0, ft_strlen(line) - 1);
		if (!h_line)
		{
			free(line);
			freeway(cli);
		}
		add_history(h_line);
		free(line);
		free(h_line);
	}
	close(fd);
}

int	ret_code(t_lst *mnsh, int ret)
{
	mnsh->exit_code = ret;
	return (ret);
}

void	handle_seg(int signum)
{
	(void)signum;
	ft_printf_fd(2, BRED "SEGFAULT\n" CRESET);
	exit(131);
}
