/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:17:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/18 15:52:24 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_array_env(t_cli **cli, char **envp)
{
	(*cli)->mnsh->env_var_lst = init_stack((*cli)->mnsh->env_var_lst, envp);
	if (!(*cli)->mnsh->env_var_lst)
		return (return_error(ERROR, "env_var_lst: Alloc ", NULL, DEBUG_MODE));
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
	(*cli)->spe_param = ft_split(SPECIAL_PARAM_LIST, ',');
	if (!(*cli)->spe_param)
		return (return_error(ERROR, "spe_param: Alloc ", NULL, DEBUG_MODE));
	return (SUCCESS);
}
