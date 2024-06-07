/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:40:12 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:13:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	display_info(char *add_msg, int debug_mode)
{
	if (debug_mode == 2)
	{
		ft_putstr_fd(BHBLU "INFO" CRESET, 1);
		if (add_msg != 0)
		{
			ft_putstr_fd(" : " BHWHT, 1);
			ft_putstr_fd(add_msg, 1);
		}
		ft_putstr_fd(CRESET "\n", 1);
	}
	else if (debug_mode == 1)
		ft_putstr_fd("\n", 1);
}
