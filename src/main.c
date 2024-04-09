/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 12:27:02 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Render prompt for while loop
 *
 * @param args
 */
void	render_prompt(t_lst *args, char **commands)
{
	char	*input;

	handle_sig(0);
	input = readline(BRED "[~] " CRESET "MINISHELL $ " BGRN "> " CRESET);
	if (!input)
	{
		free(input);
		delete_all_nodes_env(&args->env_cpy_lst);
		delete_all_nodes_env(&args->env_var_lst);
		global_free(args, commands);
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	add_history(input);
	choose(input, commands, &args);
	//free(input);
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
	t_lst	*args;
	char	**commands;

	commands = NULL;
	(void)ac;
	args = ft_calloc(1, sizeof(t_lst));
	init_lst(args, envp);
	if (av[1] && !ft_strncmp(av[1], "1", 1) && ft_strlen(av[1]) == 1)
		title_screen("Minishell", HGRN);
	while (1)
		render_prompt(args, commands);
	return (0);
}
