/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:40:12 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/02/24 17:50:35 by aska             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	return_error(int return_code, char *add_msg, void *to_free, int debug_mode)
{
	if (debug_mode == 2)
	{
		ft_putstr_fd(BRED "ERROR" CRESET, 2);
		if (add_msg != 0)
		{
			ft_putstr_fd(" : " BHWHT, 2);
			ft_putstr_fd(add_msg, 2);
		}
		ft_putstr_fd(CRESET "\n", 2);
	}
	else if (debug_mode == 1)
		ft_putstr_fd("\n", 2);
	free(to_free);
	return (return_code);
}
