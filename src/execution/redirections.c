/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:52:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 15:16:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirection(char **str, t_cli *cli)
{
	(void)cli;
	if (!str[0] || !str[1])
		return ;
	if (!ft_strncmp(str[0], ">", 1) || !ft_strncmp(str[0], "<", 2))
		printf("redirection\n");
}
