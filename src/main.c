/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/26 11:33:26 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @Main function
 *
 * @comments 		// commands = ft_split(input, ' ');
					// show_token(commands, com);
 * @param ac
 * @param av
 * @brief allocate t_lst, handle signal, handle prompt print and history
 * @return 0
 */
int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**commands;
	t_lst	**args;

	commands = NULL;
	(void)av;
	if (ac > 1)
		return (0);
	args = malloc(sizeof(t_lst));
	*args = malloc(sizeof(t_lst *) * 10);
	init_lst(args, envp);
	while (1)
	{
		handle_sig(0);
		input = readline(BOLDCYAN "MINISHELL $> " RESET);
		if (!input)
		{
			g_value = 0;
			free(input);
			input = NULL;
			printf("exit\n");
			exit(g_value);
		}
		add_history(input);
		choose(input, commands, args);
		free(input);
		input = NULL;
	}
	return (0);
}
