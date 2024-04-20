/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:01:11 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/20 12:44:18 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

//? https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html

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

int	ft_lencmparray(char *token, char **array)
{
	int	i;
	int	tmp;

	i = 0;
	while (array[i])
	{
		tmp = ft_strlen(array[i]);
		if (ft_strncmp(token, array[i++], tmp) == 0)
			return (tmp);
	}
	return (0);
}

t_token_type	token_type_discovery(char *token, t_cli *cli)
{
	if (ft_lencmparray(token, cli->quote) > 0)
	{
		cli->n_quote++;
		return (QUOTE);
	}
	if (cli->n_quote & 1)
		return (IMMUABLE);
	if (ft_lencmparray(token, cli->redirect) > 0)
		return (REDIRECTION_OPERATOR);
	if (ft_lencmparray(token, cli->control) > 0)
		return (CONTROLE_OPERATOR);
	if (ft_lencmparray(token, cli->bracket) > 0)
		return (BRACKET);
	if (cli->token == NULL || ft_iscontrol(get_token_from_index(cli->token,
				get_last_index(cli->token)), cli) > 0)
		return (COMMAND);
	return (ARGUMENT);
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
	i += ft_lencmparray(token, cli->quote);
	i += ft_lencmparray(token, cli->bracket);
	return (i);
}

void	split_into_token(t_cli *cli)
{
	int		i;
	int		offset;
	int		iter;
	char	*token_tmp;

	token_tmp = NULL;
	iter = get_last_index(cli->token) + 1;
	i = 0;
	while (cli->input[i] != 0)
	{
		if (cli->input[i] == ' ' || cli->input[i] == '\t')
			i++;
		if (cli->input[i] == 0)
			break ;
		offset = ft_lenstrtype(cli->input + i, cli);
		if (offset == 0)
			offset = get_position_of_next_meta(cli->input + i);
		token_tmp = ft_substr(cli->input, i, offset);
		if (token_tmp == NULL)
			return ;
		insert_token_end(&cli->token, ft_strtrim(token_tmp, " "),
			token_type_discovery(token_tmp, cli), iter++);
		free_char(token_tmp);
		i += offset;
	}
	cli->n_token = iter;
}
