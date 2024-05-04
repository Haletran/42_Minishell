/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:52:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/24 08:55:25 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	ft_redirection(char **str, t_lst *mnsh)
{
	(void)mnsh;
	if (!str[2] || !str[1])
		return ;
	if (!ft_strncmp(str[2], ">", 1) || !ft_strncmp(str[2], ">>", 2))
		printf("redirection\n");
}
