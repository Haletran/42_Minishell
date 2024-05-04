/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:05:39 by bapasqui         ###   ########.fr       */
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
	return (0);
}

void	freeway(t_cli *cli)
{
	delete_all_nodes_variable(&cli->variable);
	free_command_line(cli);
	close(cli->mnsh->history_fd);
	rl_clear_history();
	free_tab(cli->redirect);
	free_tab(cli->control);
	free_tab(cli->keyword);
	free_tab(cli->bracket);
	free_tab(cli->builtin);
	delete_all_nodes_env(&cli->mnsh->env_cpy_lst);
	delete_all_nodes_env(&cli->mnsh->env_var_lst);
	free(cli->mnsh->current_path);
	free_tab(cli->mnsh->env_var);
	free(cli->mnsh);
	free(cli);
}
