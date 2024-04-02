/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:47 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 18:00:19 by aska             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t	c;
	char	*mem;

	mem = (char *)memoryBlock;
	c = 0;
	while (c < size)
	{
		if (mem[c] == (char)searchedChar)
			return (&mem[c]);
		c++;
	}
	return (0);
}
