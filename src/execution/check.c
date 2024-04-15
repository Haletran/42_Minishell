/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 07:54:21 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/15 18:17:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void choose(char *input, char **commands, t_lst **args)
{
	int	i;

	i = 0;
	if (input[0] == '\0' || check_space(input))
		rl_on_new_line();
	else if (input[0] == '$')
		print_path(input + 1, *args, 1);
	else if (input[0] != '\0')
	{
		add_history(input);
		commands = ft_split(input, ' ');
		if (check_if_pipe(commands))
		{
			free_tab(commands);
			commands = ft_split(input, '|');
			while (commands[i++])
				commands[i] = ft_strtrim(commands[i], " ");
			exec_pipe(commands, *args);
		}
		else
			exec(commands, *args);
	}
	free_tab(commands);
	free_char(input);
	return ;
}




/**
 * @brief Associate commands to built-ins if needed
 *
 * @param str
 * @param args
 * @return int (true / false)
 */
int	check_commands(char **str, t_lst *args)
{
	if (!ft_strncmp(str[0], "pwd", 3) && ft_strlen(str[0]) == 3)
		return (pwd(args));
	else if ((!ft_strncmp(str[0], "echo", 4) && ft_strlen(str[0]) == 4)
		|| (!ft_strncmp(str[0], "e\"ch\"o", 5) && ft_strlen(str[0]) == 6))
		return (ft_echo(str, args));
	else if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
		return (ft_cd(str, args));
	else if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
		return (ft_export(args, str));
	else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (ft_unset(str, &args));
	else if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (ft_env(args, str));
	else if (!ft_strncmp(str[0], "<<", 2) && ft_strlen(str[0]) == 2)
		return(ft_heredoc(str, args));
	else if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
		return (ft_exit(str[1], args, str));
	return (NOT_FOUND);
}

int	check_if_fork(char **str, t_lst *args)
{
	if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
		return (ft_export(args, str));
	else if (!ft_strncmp(str[0], "<<", 2) && ft_strlen(str[0]) == 2)
		return (ft_heredoc(str, args));
	else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (ft_unset(str, &args));
	else if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (ft_env(args, str));
	return (NOT_FOUND);
}


int	check_if_path_needed(char **str)
{
	if (!ft_strncmp(str[0], "pwd", 3) && ft_strlen(str[0]) == 3)
		return (SUCCESS);
	else if ((!ft_strncmp(str[0], "echo", 4) && ft_strlen(str[0]) == 4)
		|| (!ft_strncmp(str[0], "e\"ch\"o", 5) && ft_strlen(str[0]) == 6))
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
		return (SUCCESS);
	else if (!ft_strncmp(str[0], "<<", 2) && ft_strlen(str[0]) == 2)
		return (SUCCESS);
	return (NOT_FOUND);
}
