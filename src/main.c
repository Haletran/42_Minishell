/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/30 11:48:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Render prompt for while loop
 *
 * @param mnsh
 */
void	render_prompt(t_cli *cli)
{
	handle_sig(0);
	parsing_organiser(cli);
	if (cli->rules_flag == 0)
		choose(cli);
	free_command_line(cli);
}

int	main(int ac, char **av, char **envp)
{
	t_cli	*cli;

	(void)ac;
	if (av[1] && !ft_strncmp(av[1], "1", 1) && ft_strlen(av[1]) == 1)
		title_screen("Minishell", HGRN);
	if (!envp || !*envp || check_if_path(envp) == 0)
		exit_error(1, "Error: No environment variable found", NULL, DEBUG_MODE);
	cli = NULL;
	init_organizer(&cli, envp);
	while (1)
		render_prompt(cli);
	return (cli->mnsh->exit_code);
}
