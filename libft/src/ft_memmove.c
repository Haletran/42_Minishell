/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:15:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:17:41 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*mod_dest;
	unsigned char	*mod_src;

	mod_src = (unsigned char *)src;
	mod_dest = (unsigned char *)dest;
	if (size >= 0)
	{
		if (src > dest)
			ft_memcpy(dest, src, size);
		else if (dest > src)
			while (size--)
				mod_dest[size] = mod_src[size];
	}
	return (mod_dest);
}
