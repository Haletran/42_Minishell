/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 07:54:21 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/19 15:38:00 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	choose(char *input, char **commands, t_lst **args)
{
	if (input[0] == '\0' || check_space(input))
		rl_on_new_line();
	else if (input[0] != '\0')
	{
		add_history(input);
		commands = ft_split(input, ' ');
		if (check_if_pipe(commands))
		{
			commands = ft_split(input, '|');
			// print_commands(commands);
			exec_pipe(commands, *args);
		}
		else
			exec(commands, *args);
	}
}
