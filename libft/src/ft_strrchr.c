/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:01:26 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 19:13:59 by aska             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	mod_c;
	int				i;

	mod_c = c;
	i = ft_strlen((char *)s);
	if (s[i] == mod_c)
		return ((char *)s + i);
	while (i--)
		if (s[i] == mod_c)
			return ((char *)s + i);
	return (NULL);
}
