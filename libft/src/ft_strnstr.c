/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:18:38 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:44:16 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;

	if (*little == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	while (*big != '\0' && len)
	{
		if (*big == *little)
		{
			j = 0;
			while (little[j] != 0 && big[j] == little[j] && len - j)
				j++;
			if (j == (ft_strlen((char *)little)) && len != 0)
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (0);
}
