/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:01:11 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/16 12:51:26 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//? https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html

int	get_position_of_next_meta(char *input)
{
	int i;
	int minus_position;
	
	i = 0;
	minus_position = -1;
	while(input[i++])
	{
		if (ft_ismeta(input[i]))
		{
			if(minus_position == -1)
				minus_position = i;
			else if (i < minus_position)
				minus_position = i;
			if (input[i] == 0)
				minus_position = i;
		}
	}
	if (minus_position == -1)
		minus_position = i;
	return (minus_position);
}

t_token_type	token_type_discovery(char *token, t_cli *cli)
{
	int i;
	int last_index;
	
	i =0;
	last_index = get_last_index(cli->token);
	while (cli->redirect[i])
	{
		if (ft_strcmp(token, cli->redirect[i++]) == 0)
			return (REDIRECTION_OPERATOR);
	}
	i =0;
	while (cli->control[i])
		if (ft_strcmp(token, cli->control[i++]) == 0)
			return (CONTROLE_OPERATOR);
	if (cli->token == NULL || ft_iscontrol(get_token_from_index(cli->token, last_index), cli) > 0)
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
int ft_isstroperator(char *token, t_cli *cli)
{
	int i = 0;
	int j = 0;
	int tmp;
	
	while (cli->redirect[i])
	{
		tmp = ft_strlen(cli->redirect[i]);
		if (ft_strncmp(token, cli->redirect[i++], tmp) == 0)
			return (tmp);
	}
	while (cli->control[j])
	{
		tmp = ft_strlen(cli->control[j]);
		if (ft_strncmp(token, cli->control[j++], tmp) == 0)
			return (tmp);
	}
	return (0);
}

void	split_into_token(t_cli *cli)
{
	int cursor;
	int offset;
	int iter;
	char *token_tmp= NULL;
	
	iter = 0;
	cursor = 0;
	while (cli->input[cursor] != 0)
	{
		if (cli->input[cursor] == ' ' || cli->input[cursor] == '\t' || cli->input[cursor] == '\n')
			cursor++;
		offset = ft_isstroperator(cli->input + cursor, cli);
		if (offset == 0)
			offset = get_position_of_next_meta(cli->input + cursor);
		token_tmp = ft_substr(cli->input, cursor, offset);
		if (token_tmp == NULL)
			return ;
		insert_token_end(&cli->token, ft_strtrim(token_tmp, " "), token_type_discovery(token_tmp, cli), iter++);
		free(token_tmp);
		cursor += offset;
	}
	cli->n_token = iter;
}