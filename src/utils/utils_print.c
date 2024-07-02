/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:25 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 17:20:17 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list_env(char *string, t_lst *mnsh)
{
	t_env	*current;

	current = mnsh->env_var_lst;
	while (current)
	{
		if (current->print == 0 || current->value)
			ft_printf_fd(1, "%s%s%s\n", current->key, string, current->value);
		current = current->next;
		if (!current)
			break ;
	}
}

void	print_list_export(t_env *current)
{
	while (current)
	{
		if (current->value)
		{
			if (ft_strcmp(current->key, "_"))
				ft_printf_fd(1, "declare -x %s=\"%s\"\n", current->key,
					current->value);
		}
		else
			ft_printf_fd(1, "declare -x %s\n", current->key);
		current = current->next;
	}
}

void	print_error(int i, char *str)
{
	if (i == NOT_FOUND)
		ft_printf_fd(2, "minishell: %s: command not found\n", str);
	else if (i == FORK_FAILED)
		ft_printf_fd(2, CRESET "fork failed\n");
	else if (i == NO_FILE)
		ft_printf_fd(2, "%s: No such file or directory\n", str);
	else if (i == IS_DIRECTORY)
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
	else if (i == PERMISSION_DENIED)
		ft_printf_fd(2, "minishell: %s: Permission denied\n", str);
	else if (i == -50)
		ft_printf_fd(2, "minishell: quotes not closed\n");
}
