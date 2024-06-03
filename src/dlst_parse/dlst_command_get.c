/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_command_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:51:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/03 15:30:24 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

t_com	*get_last_command(t_com *com)
{
	t_com *tmp;

	tmp = com;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}