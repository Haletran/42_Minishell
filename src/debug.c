/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:50 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/15 07:59:45 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all_in_cli(t_cli *cli)
{
	ft_printf(HRED "Input :\t" BYEL "%s\t " HRED ":: n_token :" BYEL " %i\t",
		cli->input, cli->n_token);
	ft_printf(HRED "n_quote :" BYEL "%i\t " HRED "n_dquote :" BYEL "%i\n",
		cli->n_quote, cli->n_dquote);
	ft_printf(HRED "heredoc :" BYEL "%i\t\n\n", cli->heredoc);
	ft_printf(HRED "Token list :\n" CRESET);
	print_all_token(cli->token);
	ft_printf("\n");
}

void	print_all_token(t_token *token)
{
	t_token	*head;
	char	*type[] = {"COMMAND", "CONTROLE_OPERATOR", "REDIRECTION_OPERATOR",
			"ARGUMENT", "QUOTE", "DQUOTE", "BRACKET", "FREEZE", "HEREDOC",
			"DELIMITER", "IMMUTABLE", "BUILTIN", "KEYWORD"};

	head = token;
	while (token)
	{
		ft_printf(WHT "Index:" BHGRN " %i" CRESET, token->index);
		if (ft_intlen(token->index, 0) < 2)
			ft_printf("  ");
		else
			ft_printf(" ");
		ft_printf(WHT "| Token:" BHGRN " \"%s\"" CRESET, token->token);
		if (2 + ft_strlen(token->token) < 5)
			ft_printf("\t\t");
		else
			ft_printf("\t");
		ft_printf(WHT "| Type:" BHGRN "%s\n" CRESET "", type[token->type]);
		token = token->next;
	}
	token = head;
}

void	print_all_com(t_com *com)
{
	t_com	*head;
	int		i;
	char	*type[] = {"COMMAND", "CONTROLE_OPERATOR", "REDIRECTION_OPERATOR",
			"ARGUMENT", "QUOTE", "DQUOTE", "BRACKET", "FREEZE", "HEREDOC",
			"DELIMITER", "IMMUTABLE", "BUILTIN", "KEYWORD"};

	head = com;
	ft_printf(BHRED "PRINT ALL COMMANDS\n\n" CRESET);
	while (head)
	{
		i = -1;
		ft_printf(WHT "Index:" BHGRN " %i" CRESET, head->index);
		ft_printf(WHT "| Type:" BHGRN "%s\n" CRESET, type[head->type]);
		if (ft_intlen(head->index, 0) < 2)
			ft_printf("  ");
		else
			ft_printf(" ");
		while (head->command[++i] != NULL)
			ft_printf(WHT "\nCommand[%i]:" BHGRN " \"%s\"" CRESET, i,
				head->command[i]);
		if (head->redirection != NULL)
			ft_printf(WHT "| Redirection:" BHGRN " \"%s\"" CRESET,
				head->redirection);
		ft_printf(WHT "\n\nPipe:" BHGRN " %i" CRESET, head->pipe);
		ft_printf(WHT "| Path:" BHGRN " \"%s\"\n\n" CRESET, head->env_path);
		head = head->next;
	}
	ft_printf(BHRED "\nEND PRINT ALL COMMANDS\n\n" CRESET);
}

void	debug(t_cli *cli, char *add_msg)
{
	printf(BHCYN "\t\t\t#########\n\t\t%s\n\t\t\t#########\n\n" CRESET,
		add_msg);
	print_all_in_cli(cli);
	print_all_com(cli->com);
	//printf("REDIRECTION %s\n", cli->com->redirection);
}

void	print_type(t_token *token)
{
	char	*type[] = {"COMMAND", "CONTROLE_OPERATOR", "REDIRECTION_OPERATOR",
			"ARGUMENT", "QUOTE", "DQUOTE", "BRACKET", "FREEZE", "HEREDOC",
			"DELIMITER", "IMMUTABLE", "BUILTIN", "KEYWORD"};

	ft_printf("Type: %s\n", type[token->type]);
}

void	print_type_com(t_com *com)
{
	char *type[] = {"COMMAND", "CONTROLE_OPERATOR", "REDIRECTION_OPERATOR",
		"ARGUMENT", "QUOTE", "DQUOTE", "BRACKET", "FREEZE", "HEREDOC",
		"DELIMITER", "IMMUTABLE", "BUILTIN", "KEYWORD"};

	ft_printf("Type: %s\n", type[com->type]);
}