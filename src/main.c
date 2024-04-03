/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/03 10:55:04 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Render prompt for while loop
 *
 * @param args
 */
void	render_prompt(t_lst **args, char **commands)
{
	char	*input;

	handle_sig(0);
	input = readline("MINISHELL $ " BGRN "> " CRESET);
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
	t_lst	**args;
	char	**commands;

	title_screen("minishell", HGRN);
	commands = NULL;
	(void)av;
	if (ac != 1)
		return (0);
	args = malloc(sizeof(t_lst));
	init_lst(args, envp);
	while (1)
		render_prompt(args, commands);
	return (0);
}
