/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:15:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:45:00 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = 0;
	while (i != n)
		t[i++] = c;
	return (s);
}
