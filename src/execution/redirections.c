/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:52:09 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:34:40 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirection(char **str, t_lst *mnsh)
{
	(void)mnsh;
	if (!str[2] || !str[1])
		return ;
	if (!ft_strncmp(str[2], ">", 1) || !ft_strncmp(str[2], ">>", 2))
		printf("redirection\n");
}
