/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:28:43 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/24 08:55:24 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	pwd(t_lst *mnsh)
{
	char *path;

	path = search_path("PWD", mnsh);
	printf("%s\n", path);
	return (SUCCESS);
}
