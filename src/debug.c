/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:50 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/30 16:04:43 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all_in_cli(t_cli *cli)
{
	ft_printf(HRED "n_token\t:" BYEL " %i\t" HRED "| Input\t: " BYEL "%s\n",
		cli->n_token, cli->input);
	ft_printf(HRED "flag_quote\t: " BYEL "%i\t" HRED "| flag_dquote\t: " BYEL "%i\n",
		cli->flag_quote, cli->flag_dquote);
	ft_printf(HRED "heredoc\t: " BYEL "%i\t" HRED "| Exit_code\t: " BHRED "%i\n",
		cli->heredoc, cli->mnsh->exit_code);
	ft_printf(HRED "Token list\t:\n" CRESET);
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
	//if (com->redirection)
	//	printf(WHT "| Redirection :" BHGRN " \"%s\"" CRESET, com->redirection);
	ft_printf(BHRED "\nEND PRINT ALL COMMANDS\n\n" CRESET);
}

void	debug(t_cli *cli, char *add_msg)
{
	if (DEBUG == 1)
	{
		printf(BHCYN "\t\t\t#########\n\t\t%s\n\t\t\t#########\n\n" CRESET,
			add_msg);
		print_all_in_cli(cli);
		print_all_com(cli->com);
		ft_printf("\t##########\t##########\t##########\t##########\n\n");
	}
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