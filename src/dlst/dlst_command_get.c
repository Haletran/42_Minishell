/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_command_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/06 19:37:59 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_com	*get_last_command(t_com *com)
{
	t_com *tmp;

	tmp = com;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}