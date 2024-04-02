/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:15:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 17:56:38 by aska             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, 0, n));
}
