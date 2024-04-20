/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:50 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/20 14:27:12 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    print_all_in_cli(t_cli *cli)
{
    ft_printf( HRED"Input :\t" BYEL "%s\t "HRED":: n_token :" BYEL" %i\t", cli->input, cli->n_token);
    ft_printf( HRED"n_quote :\t" BYEL "%i\n\n", cli->n_quote);
    print_all_token(cli->token);
    ft_printf("\n");
}

void    print_all_token(t_token *token)
{
    t_token   *head;
    char *type[] = {"COMMAND", "CONTROLE_OPERATOR", "REDIRECTION_OPERATOR", "ARGUMENT", "QUOTE", "BRACKET", "IMMUABLE"}; 

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