/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/01 16:13:18 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Render prompt for while loop
 *
 * @param mnsh
 */
void	render_prompt(t_cli *cli)
{
	handle_sig(0);
	parsing_organiser(cli);
	if (!cli->input[0])
		rl_on_new_line();
	else if (cli->rules_flag == 0)
		exec_pipe(cli);
	cli->input = free_char(cli->input);
	free_command_line(cli);
}

int	main(int ac, char **av, char **envp)
{
	t_cli	*cli;

	if (ac == 2)
	{
		if (av[1] && !ft_strncmp(av[1], "-c", 2))
			ft_printf_fd(2, "minishell: -c: option requires an argument\n");
		else if (av[1] && ft_strncmp(av[1], "-c", 2))
			ft_printf_fd(2, "minishell: %s: invalid option\n", av[1]);
		exit(2);
	}
	//title_screen("MINISHELL", GRN);
	//ft_printf("\033[1;36m[ Developed by ]\033[0m ygaiffie & bapasqui\033[0m\n\n");
	if (!envp || !*envp || check_if_path(envp) == 0)
		exit_error(1, "Error: No environment variable found", NULL, DEBUG_MODE);
	cli = NULL;
	init_organizer(&cli, envp, av);
	while (1)
		render_prompt(cli);
	return (cli->mnsh->exit_code);
}
