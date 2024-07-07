/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:15:28 by baptiste          #+#    #+#             */
/*   Updated: 2024/07/07 17:36:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_organizer(t_cli **cli, char **envp, char **av)
{
	int	err;

	err = 0;
	err = first_allocation(cli, envp);
	if (err == ERROR)
		freeway(*cli);
	if (av[1] != NULL && ft_strcmp(av[1], "-c") == 0)
	{
		(*cli)->av = ft_strdup(av[2]);
		if (!(*cli)->av)
		{
			freeway(*cli);
			exit_error(1, "Error: Malloc failed", NULL, DEBUG_MODE);
		}
	}
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

t_env	*init_stack(t_env *env, char **str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		key = ft_substr(str[i], 0, ft_strlen_endc(str[i], '='));
		if (!key)
			return (NULL);
		value = ft_strdup(ft_strchr(str[i++], '=') + 1);
		if (!value)
			free_char(key);
		if (!value)
			return (NULL);
		insert_env_end(&env, ft_strdup(key), ft_strdup(value));
		if ((!env) || (!env->key) || (!env->value))
			return (NULL);
		key = free_char(key);
		value = free_char(value);
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
