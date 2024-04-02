/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:15:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 18:06:08 by aska             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*mod_dest;
	unsigned char	*mod_src;

	if (!src && !dest)
		return (0);
	mod_src = (unsigned char *)src;
	mod_dest = (unsigned char *)dest;
	i = 0;
	while (i != n)
	{
		mod_dest[i] = mod_src[i];
		i++;
	}
	return (dest);
}
