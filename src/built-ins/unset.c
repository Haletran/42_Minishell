/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:12:03 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/01 18:01:21 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	delete(t_lst *args, int len)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = malloc(sizeof(char *) * (get_nbargs(args->env_var) + 1));
	while (j < len)
	{
		tmp[j] = args->env_var[j];
		j++;
	}
	j++;
	while (args->env_var[j])
	{
		tmp[j - 1] = args->env_var[j];
		j++;
	}
	free(args->env_var);
	free(args->env_cpy);
	tmp[j - 1] = NULL;
	args->env_var = cpy(tmp, args->env_var);
	args->env_cpy = cpy(tmp, args->env_cpy);
	free(tmp);
	return (SUCCESS);
}

int	ft_unset(char **str, t_lst **args)
{
	int	len;
	int	i;

	len = 0;
	i = 1;
	while (str[i])
	{
		len = 0;
		str[i] = ft_strjoin(str[i], "=");
		while ((*args)->env_var[len])
		{
			if (!ft_strncmp((*args)->env_var[len], str[i], ft_strlen(str[i])))
				break ;
			len++;
		}
		delete ((*args), len);
		i++;
	}
	return (SUCCESS);
}
