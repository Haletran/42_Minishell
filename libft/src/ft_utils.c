/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:15:00 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/26 18:24:14 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_rev_wr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	while (i != 0)
		write(1, &str[--i], 1);
}
