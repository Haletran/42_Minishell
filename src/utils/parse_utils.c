/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:12:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/03 12:30:13 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	i += ft_lencmparray(token, cli->keyword);
	return (i);
}

int	is_error_path(char *str, char **path, t_lst *mnsh, char *full_path)
{
	(void)path;
	if (full_path == NULL)
	{
		free_char(full_path);
		mnsh->exit_code = 127;
		return (EXIT_FAILURE);
	}
	if (access(full_path, F_OK | R_OK) == -1)
	{
		if (check_if_builtin(str) == SUCCESS)
			return (EXIT_SUCCESS);
		ft_printf_fd(2, "%s : command not found\n", str);
		free_char(full_path);
		mnsh->exit_code = 127;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// GUILLEMETS NOT WORKING ANYMORE
t_token_type	token_type_rediscovery(t_token *tok, t_cli *cli)
{
	if (cli->heredoc == 1 && ft_isthis(" \t\n", tok->token[0]) == 0)
		return (quote_n_heredoc_census(tok->token, cli));
	if (ft_isthis("<", tok->token[0]) > 0)
		return (quote_n_heredoc_census(tok->token, cli));
	/* 	if (cli->flag_dquote & 1)
			return (FREEZE);
		if (cli->flag_quote & 1)
			return (IMMUTABLE); */
	if (tok->type == HEREDOC)
		return (HEREDOC);
	if (ft_lencmparray(tok->token, cli->redirect) > 0)
		return (REDIRECTION_OPERATOR);
	if (ft_lencmparray(tok->token, cli->control) > 0)
		return (CONTROLE_OPERATOR);
	if (ft_lencmparray(tok->token, cli->bracket) > 0)
		return (BRACKET);
	if (command_census(tok, cli) == COMMAND)
		return (COMMAND);
	return (ARGUMENT);
}
