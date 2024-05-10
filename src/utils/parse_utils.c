/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:12:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/10 21:53:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <string.h>

int	ft_lencmparray(char *token, char **array)
{
    int	i;
    int	tmp;
    int	command_len;

    command_len = 0;
	i = 0;
    while (token[command_len] && token[command_len] != ' ')
        command_len++;
    while (array[i])
    {
        tmp = ft_strlen(array[i]);
        if (tmp == command_len && ft_strncmp(token, array[i], tmp) == 0)
            return (tmp);
        i++;
    }
    return (0);
}

int	get_position_of_next_meta(char *input)
{
	int	i;
	int	minus_position;

	i = 0;
	minus_position = -1;
	while (input[i])
	{
		if (ft_ismeta(input[i]))
		{
			if (minus_position == -1)
				minus_position = i;
			else if (i < minus_position)
				minus_position = i;
			if (input[i] == 0)
				minus_position = i;
		}
		i++;
	}
	if (minus_position == -1)
		minus_position = i;
	return (minus_position);
}

/**
 * @brief Fonction qui permet de savoir si le token est un operateur
 *
 * @param token Token a tester
 * @param cli Contient les operateurs
 * @return int Retourne la taille de l'operateur si c'est un operateur, 0 sinon
 */
int	ft_lenstrtype(char *token, t_cli *cli)
{
	int	i;

	i = 0;
	i += ft_lencmparray(token, cli->redirect);
	i += ft_lencmparray(token, cli->control);
	i += ft_lencmparray(token, cli->bracket);
	return (i);
}
