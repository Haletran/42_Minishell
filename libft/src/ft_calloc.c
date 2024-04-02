/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:22:33 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 17:43:42 by aska             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	size_t	mem_size;
	void	*mem_init;

	if (elementCount <= 0 || elementSize <= 0)
		return (malloc(0));
	if ((long long)elementCount < 0 || (long long)elementSize < 0)
		return (0);
	mem_size = elementCount * elementSize;
	mem_init = malloc(mem_size);
	if (!(mem_init))
		return (NULL);
	return (ft_bzero(mem_init, mem_size));
}
