/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:15:28 by baptiste          #+#    #+#             */
/*   Updated: 2024/06/26 13:56:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_organizer(t_cli **cli, char **envp)
{
	int	err;

	err = 0;
	err = first_allocation(cli, envp);
	if (err == ERROR)
		freeway(*cli);
	err = init_array_env(cli, envp);
	if (err == ERROR)
		freeway(*cli);
	err = init_array(cli);
	if (err == ERROR)
		freeway(*cli);
	err = init_data_parsing(cli);
	if (err == ERROR)
		freeway(*cli);
}

int	first_allocation(t_cli **cli, char **envp)
{
	(void)envp;
	*cli = ft_calloc(1, sizeof(t_cli));
	if (!*cli)
		return (return_error(ERROR, "cli: Alloc ", NULL, DEBUG_MODE));
	(*cli)->mnsh = ft_calloc(1, sizeof(t_lst));
	if (!(*cli)->mnsh)
		return (return_error(ERROR, "mnsh: Alloc ", NULL, DEBUG_MODE));
	return (SUCCESS);
}

void	init_fd_history(t_cli **cli)
{
	if (access(".mini_history", F_OK) != -1)
	{
		(*cli)->mnsh->history_fd = open(".mini_history", O_RDWR | O_APPEND,
				0640);
		historyze(*cli);
	}
	else
	{
		display_info("History : Dont exist\n", DEBUG_MODE);
		(*cli)->mnsh->history_fd = open(".mini_history",
				O_RDWR | O_CREAT | O_TRUNC, 0640);
	}
}

t_env	*init_stack(t_env *env, char **str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		tmp = ft_split(str[i], '=');
		if (!tmp)
			return (NULL);
		insert_env_end(&env, ft_strdup(tmp[0]), ft_strdup(tmp[1]));
		if (!env)
			return (NULL);
		if (!env->key || !env->value)
			return (NULL);
		i++;
		free_tab(tmp);
	}
	return (env);
}

int	init_data_parsing(t_cli **cli)
{
	(*cli)->flag_dquote = 0;
	(*cli)->flag_quote = 0;
	(*cli)->n_quote = 0;
	(*cli)->n_dquote = 0;
	(*cli)->n_token = 0;
	(*cli)->n_com = 0;
	(*cli)->index = 0;
	(*cli)->com = NULL;
	(*cli)->mnsh->syntax_error = 0;
	(*cli)->token = NULL;
	(*cli)->commands = NULL;
	(*cli)->mnsh->exit_code = 0;
	(*cli)->heredoc = 0;
	(*cli)->mnsh->ctrl_c = 0;
	(*cli)->mnsh->outfile_check = 0;
	(*cli)->rules_flag = 0;
	(*cli)->mnsh->not_fork = 0;
	return (SUCCESS);
}
