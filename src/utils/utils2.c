/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:22 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/16 14:12:57 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_nbargs(char **str)
{
	int	size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}

int get_exit_code(t_lst *mnsh)
{
	if (WIFEXITED(mnsh->exit_code))
		return (mnsh->exit_code = WEXITSTATUS(mnsh->exit_code));
	else if (WIFSIGNALED(mnsh->exit_code))
		return (mnsh->exit_code = WTERMSIG(mnsh->exit_code) + 128);
	else if (WIFSTOPPED(mnsh->exit_code))
		return (mnsh->exit_code = WSTOPSIG(mnsh->exit_code));
	return (0);
}

int	check_if_pipe(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(str[i], '|'))
			return (1);
		i++;
	}
	return (0);
}

t_env	*sort_in_ascii(t_env *list)
{
	t_env	*current;
	t_env	*index;
	char	*tmp_key;
	char	*tmp_value;

	current = list;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(current->key, index->key) > 0)
			{
				tmp_key = current->key;
				tmp_value = current->value;
				current->key = index->key;
				current->value = index->value;
				index->key = tmp_key;
				index->value = tmp_value;
			}
			index = index->next;
		}
		current = current->next;
	}
	return (list);
}

//[a-zA-Z_]{1,}[a-zA-Z0-9_]{0,}
int	check_if_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '$' && str[i] != '='
			&& str[i] != '+' && str[i] != '_' && str[i] != '/' && str[i] != '.')
			return (ERROR);
		if (str[i] == '-')
			return (ERROR);
/* 		if (ft_isdigit(str[i]) == TRUE && str[i - 1] != '=')
			return (ERROR); */
		i++;
	}
	i = 0;
	while(str[i] != '=' )
	{
		if (ft_isdigit(str[i]) == TRUE && str[i - 1] != '=')
			return (ERROR);
		i++;
	}

	return (SUCCESS);
}

int	ft_cpy(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

char	**cpy(char **src, char **dest)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!dest || !src)
		return (NULL);
	while (src[len] != NULL)
		len++;
	dest = malloc((len + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (src[i] != NULL)
	{
		dest[i] = strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
