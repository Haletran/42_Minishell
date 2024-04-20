/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/20 14:19:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Render prompt for while loop
 *
 * @param args
 */
void	render_prompt(t_cli *cli)
{
	handle_sig(0);
	parsing_organiser(cli);
	choose(cli, cli->commands, &cli->args);
	delete_all_nodes_token(&cli->token);
}

//ft_printf_fd(cli->args->history_fd, "%s%s", cli->input, "\0");

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
	
	t_cli	*cli;

	(void)ac;
	cli = ft_calloc(1, sizeof(t_cli));
	cli->commands = NULL;
	cli->args = ft_calloc(1, sizeof(t_lst));
	init_lst(cli->args, envp);
	init_meta_and_operat(&cli);
	if (av[1] && !ft_strncmp(av[1], "1", 1) && ft_strlen(av[1]) == 1)
		title_screen("Minishell", HGRN);
	while (1)
		render_prompt(cli);
	return (0);
}
