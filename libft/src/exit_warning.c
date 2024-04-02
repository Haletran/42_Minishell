/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_warning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:40:12 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/02/24 17:52:07 by aska             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	exit_warning(int return_code, char *add_msg, void *to_free, int debug_mode)
{
	if (debug_mode == 2)
	{
		ft_putstr_fd(BYEL "WARNING" CRESET, 1);
		if (add_msg != 0)
		{
			ft_putstr_fd(" : " BHWHT, 1);
			ft_putstr_fd(add_msg, 1);
		}
		ft_putstr_fd(CRESET "\n", 1);
	}
	else if (debug_mode == 1)
		ft_putstr_fd("\n", 1);
	free(to_free);
	exit(return_code);
}
