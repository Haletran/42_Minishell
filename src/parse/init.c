/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:15:28 by baptiste          #+#    #+#             */
/*   Updated: 2024/05/27 13:31:40 by bapasqui         ###   ########.fr       */
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
	init_fd_history(cli);
}

int	first_allocation(t_cli **cli, char **envp)
{
	*cli = ft_calloc(1, sizeof(t_cli));
	if (!*cli)
		return (return_error(ERROR, "cli: Alloc ", NULL, DEBUG_MODE));
	(*cli)->mnsh = ft_calloc(1, sizeof(t_lst));
	if (!(*cli)->mnsh)
		return (return_error(ERROR, "mnsh: Alloc ", NULL, DEBUG_MODE));
	(*cli)->mnsh->env_var = ft_calloc(1, sizeof(char) * get_len(envp));
	if (!(*cli)->mnsh->env_var)
		return (return_error(ERROR, "env_var: Alloc ", cli, DEBUG_MODE));
	return (SUCCESS);
}

int	init_array_env(t_cli **cli, char **envp)
{
	int	err;

	err = 0;
	(*cli)->mnsh->env_var_lst = init_stack((*cli)->mnsh->env_var_lst, envp);
	if (!(*cli)->mnsh->env_var_lst)
		return (return_error(ERROR, "env_var_lst: Alloc ", NULL, DEBUG_MODE));
	(*cli)->mnsh->env_cpy_lst = init_stack((*cli)->mnsh->env_cpy_lst, envp);
	if (!(*cli)->mnsh->env_cpy_lst)
		return (return_error(ERROR, "env_cpy_lst: Alloc ", NULL, DEBUG_MODE));
	err = ft_cpy((*cli)->mnsh->env_var, envp);
	if (err == ERROR)
		return (return_error(ERROR, "ft_cpy: Alloc ", NULL, DEBUG_MODE));
	return (SUCCESS);
}

int	init_array(t_cli **cli)
{
	(*cli)->redirect = ft_split(REDICRECT_OPERAT_LIST, ',');
	if (!(*cli)->redirect)
		return (return_error(ERROR, "redirect: Alloc ", NULL, DEBUG_MODE));
	(*cli)->control = ft_split(CONTROL_OPERAT_LIST, ',');
	if (!(*cli)->control)
		return (return_error(ERROR, "control: Alloc ", NULL, DEBUG_MODE));
	(*cli)->keyword = ft_split(KEYWORD_LIST, ',');
	if (!(*cli)->keyword)
		return (return_error(ERROR, "Keyword: Alloc ", NULL, DEBUG_MODE));
	(*cli)->bracket = ft_split(BRACKET_LIST, ',');
	if (!(*cli)->bracket)
		return (return_error(ERROR, "bracket: Alloc ", NULL, DEBUG_MODE));
	(*cli)->builtin = ft_split(BUILTIN_LIST, ',');
	if (!(*cli)->builtin)
		return (return_error(ERROR, "builtin: Alloc ", NULL, DEBUG_MODE));
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
	return (SUCCESS);
}
