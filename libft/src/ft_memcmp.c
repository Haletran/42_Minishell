/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:29:28 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/27 14:58:52 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cast_s1;
	unsigned char	*cast_s2;
	size_t			i;

	if (n == 0)
		return (0);
	cast_s1 = (unsigned char *)s1;
	cast_s2 = (unsigned char *)s2;
	i = 0;
	while (cast_s1[i] == cast_s2[i] && i < (n - 1))
		i++;
	return (cast_s1[i] - cast_s2[i]);
}
