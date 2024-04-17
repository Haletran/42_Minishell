/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/17 18:02:50 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Render prompt for while loop
 *
 * @param args
 */
void	render_prompt(t_lst *args, char **commands, t_cli *cli)
{
	handle_sig(0);
	cli->input = readline(BRED "[~] " CRESET "MINISHELL $ " BGRN "> " CRESET);
	if (!cli->input)
	{
		free(cli->input);
		free_cli(cli);
		global_free(args, commands);
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	add_history(cli->input);
	parsing_organiser(cli);
	choose(cli, commands, &args);
	if (cli->token->token)
		delete_all_nodes_token(&cli->token);
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
	t_lst	*args;
	t_cli	*cli;
	char	**commands;

	commands = NULL;
	(void)ac;
	args = ft_calloc(1, sizeof(t_lst));
	cli = ft_calloc(1, sizeof(t_cli));
	init_lst(args, envp);
	init_meta_and_operat(&cli);
	if (av[1] && !ft_strncmp(av[1], "1", 1) && ft_strlen(av[1]) == 1)
		title_screen("Minishell", HGRN);
	while (1)
		render_prompt(args, commands, cli);
	return (0);
}
