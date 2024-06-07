/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:52:46 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:18:18 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_intlen(int nbr, int count)
{
	if (nbr == -2147483648)
		nbr++;
	if (nbr <= 0)
	{
		nbr = -nbr;
		count++;
	}
	while (nbr > 0)
	{
		nbr -= nbr % 10;
		nbr /= 10;
		count++;
	}
	return (count);
}
