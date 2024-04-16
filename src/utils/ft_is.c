/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:55:55 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/12 10:48:40 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int ft_ismeta(char c)
{
	int i; 
    
    i = 0;
    while(META_LIST[i])
    {
        if (c == META_LIST[i])
            return (c);
        i++;
    }
	return (0);
}

int ft_iscontrol(char *token, t_cli *cli)
{
	int j = 0;
	
	while (cli->control[j])
	{
		if (ft_strcmp(token, cli->control[j++]) == 0)
			return (1);
	}
	return (0);
}

int ft_isredirect(char *token, t_cli *cli)
{
	int i = 0;
	
	while (cli->redirect[i])
	{
		if (ft_strcmp(token, cli->redirect[i++]) == 0)
			return (1);
	}
	return (0);
}